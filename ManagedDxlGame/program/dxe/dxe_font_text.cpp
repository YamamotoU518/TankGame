#pragma warning(disable:4819)
#include "DxLib.h"
#include "dxe_font_text.h"
#include "../dxe/dxe_prototype.h"
#include "../dxe_build_setting.h"

namespace dxe {

	DXE_PROTOTYPE_GET_DELTA_TIME;
	DXE_PROTOTYPE_GET_RECT_ORIGIN_LOCATION;
	DXE_PROTOTYPE_GET_FONT_PATH_FROM_NAME;
	DXE_PROTOTYPE_IS_ENABLE_FONT_PATH;

	//--------------------------------------------------------------------------------------------------------------------------
	Shared<FontText> FontText::Create
		( int32_t font_size
		, const std::string& font_name
		, int32_t quality
		, int32_t thick
		, int32_t egge_size ) {

		Shared<FontText> text = std::shared_ptr<FontText>(new FontText());
		text->font_name_ = font_name;
		text->font_size_ = font_size;
		text->thick_ = thick;
		text->quality_ = quality;
		text->edge_size_ = egge_size;
		text->refresh();
		return text;
	}

	//--------------------------------------------------------------------------------------------------------------------------
	Shared<FontText> FontText::CreateAnimation
		( int32_t font_size
		, const std::string& font_name
		, int32_t quality
		, int32_t thick
		, int32_t egge_size ) {
		Shared<FontText> text = Create(font_size, font_name, quality, thick, egge_size);
		text->anim_seek_ = tnl::SeekUnit::Create(DXE_FIX_FPS, 0, 3.0f, tnl::SeekUnit::ePlayMode::SINGLE, tnl::SeekUnit::ePlayDir::FORWARD);
		return text;
	}

	//--------------------------------------------------------------------------------------------------------------------------
	FontText::~FontText() {
		DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
		if (-1 < handle_) DeleteFontToHandle(handle_);
	}

	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::setFont(const std::string& font_name) {
		{
			DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
			font_name_ = font_name;
		}
		refresh();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::setScale(const tnl::Vector2f& scale) {
		DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
		scale_ = scale;
		is_extend_ = true;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::setFontSize(const int32_t& size) {
		{
			DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
			font_size_ = size;
		}
		refresh();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::setThick(const int32_t& thick) {
		{
			DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
			thick_ = thick;
		}
		refresh();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::setQuality(const int32_t& quality) {
		{
			DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
			quality_ = quality;
		}
		refresh();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::setEdgeSize(const int32_t& egge_size) {
		{
			DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
			edge_size_ = egge_size;
		}
		refresh();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	Shared<FontText> FontText::createClone(const Shared<FontText>& origine) {
		Shared<FontText> text = std::shared_ptr<FontText>(new FontText());
		text->base_text_ = origine->base_text_;
		text->font_name_ = origine->font_name_;
		text->scale_ = origine->scale_;
		text->font_size_ = origine->font_size_;
		text->color_ = origine->color_;
		text->thick_ = origine->thick_;
		text->quality_ = origine->quality_;
		text->edge_color_ = origine->edge_color_;
		text->edge_size_ = origine->edge_size_;
		text->is_extend_ = origine->is_extend_;
		text->refresh();
		return text;
	}

	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::refresh() {
		if (!dxe::IsEnableFontPath(font_name_.c_str())) {
			throw std::runtime_error(" FontText::refresh font path not found error ");
		}
		DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
		if (-1 < handle_) DeleteFontToHandle(handle_);
		handle_ = CreateFontToHandle(font_name_.c_str(), font_size_, thick_, quality_, -1, edge_size_);
	}

	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::draw() {

		tnl::Vector2f drawpos = position_;
		int size_x, size_y, line_count;
		GetDrawStringSizeToHandle(&size_x, &size_y, &line_count, base_text_.c_str(), (int)base_text_.length(), handle_);
		GetRectOriginLocatePosition(drawpos.x, drawpos.y, (int)(size_x * scale_.x), (int)(size_y * scale_.y), location_);

		if (anim_seek_) {
			if (is_extend_) DrawExtendStringFToHandle(drawpos.x, drawpos.y, scale_.x, scale_.y, anim_draw_text_.c_str(), color_, handle_, edge_color_);
			else			DrawStringFToHandle(drawpos.x, drawpos.y, anim_draw_text_.c_str(), color_, handle_, edge_color_);
		}
		else {
			if (is_extend_) DrawExtendStringFToHandle(drawpos.x, drawpos.y, scale_.x, scale_.y, base_text_.c_str(), color_, handle_, edge_color_);
			else			DrawStringFToHandle(drawpos.x, drawpos.y, base_text_.c_str(), color_, handle_, edge_color_);
		}

		//DrawCircle(position_.x, position_.y, 3, GetColor(255, 0, 0));
	}


	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::setString(const std::string& base_text) {
		{
			DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
			base_text_ = base_text;
		}
		if (!anim_seek_) return;
		int32_t length = tnl::GetSJisLength(base_text_);
		anim_seek_->setTotalTime(static_cast<float>(length) * anim_wait_time_);
	}

	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::setAnimWaitTime(float wait_time) {
		if (!anim_seek_) return;
		{
			DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
			anim_wait_time_ = wait_time;
		}
		if (base_text_.empty()) return;
		int32_t length = tnl::GetSJisLength(base_text_);
		anim_seek_->setTotalTime( static_cast<float>(length) * anim_wait_time_ );
	}

	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::setAnimTimeScale(float time_scale) {
		if (!anim_seek_) return;
		{
			DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
			anim_time_scale_ = (0 > anim_time_scale_) ? 0 : anim_time_scale_;
			anim_time_scale_ = time_scale;
		}
		anim_seek_->setTimeScale(anim_time_scale_);
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::addAnimTimeScale(float add_scale) {
		if (!anim_seek_) return;
		{
			DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
			anim_time_scale_ += add_scale;
			anim_time_scale_ = (0 > anim_time_scale_) ? 0 : anim_time_scale_;
		}
		anim_seek_->setTimeScale(anim_time_scale_);
	}

	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::updateAnimation() {
		if (!anim_seek_) return;
		if (anim_seek_->getCondition() != tnl::SeekUnit::eCondition::PLAYING) return;
		anim_seek_->update(GetDeltaTime());

		int32_t length = static_cast<int32_t>( base_text_.length() );
		int32_t current = static_cast<int32_t>(static_cast<float>(length) * anim_seek_->getSeekRate());
		if (anim_draw_text_.length() > current) return;

		int32_t cutpos = 0;
		for (cutpos = 0; cutpos < current; ++cutpos) {
			unsigned char byte = base_text_[cutpos];
			if (tnl::IsSjisMultiUpbyte(byte)) {
				cutpos += 1;
				continue;
			}
		}
		std::string cutstr = base_text_.substr(0, cutpos);
		if (anim_draw_text_ == cutstr) return;
		std::string addstr = cutstr.substr(anim_draw_text_.length(), -1);

		{
			DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
			anim_draw_text_ = cutstr;
		}

		if (addstr[0] == ' ') return;
		if (addstr[0] == '\n') return;
		if (addstr[addstr.length() - 1] == ' ') return;
		if (addstr[addstr.length() - 1] == '\n') return;
		if (anim_update_callback_) anim_update_callback_();

	}
	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::playAnimation() {
		if (!anim_seek_) return;
		anim_seek_->play() ;
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::pauseAnimation() {
		if (!anim_seek_) return;
		anim_seek_->pause();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::restartAnimation() {
		if (!anim_seek_) return;
		anim_seek_->restart();
		anim_draw_text_.clear();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::finishAnimation() {
		if (!anim_seek_) return;
		anim_seek_->jumpSeekRate(1.0f);
	}

	//--------------------------------------------------------------------------------------------------------------------------
	tnl::SeekUnit::eCondition FontText::getAnimCondition() {
		if (!anim_seek_) return tnl::SeekUnit::eCondition::STANDBY;
		return anim_seek_->getCondition();
	}
	//--------------------------------------------------------------------------------------------------------------------------
	void FontText::setAnimUpdateCallback(const std::function<void()>& callback) {
		DXE_FONT_TEXT_LOCK_GUARD_MUTEX();
		anim_update_callback_ = callback;
	}

}
