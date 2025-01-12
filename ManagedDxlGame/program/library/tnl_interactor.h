#pragma once
#include <vector>
#include <functional>
#include <type_traits>
#include <mutex>
#include "tnl_using.h"


/* �}���`�X���b�h�𗘗p����v���W�F�N�g�ł� tnl_build_setting.h �� TNL_BUILD_SWITCH_USE_MULTI_THREDING �� true �ɐݒ肵�Ă������� */
#if TNL_BUILD_SWITCH_USE_MULTI_THREDING
#define TNL_INTERACTOR_NOT_USER_CALL_LOCK_GUARD_MUTEX() std::lock_guard<std::mutex> lock(interactor_mutex_);
#else
#define TNL_INTERACTOR_NOT_USER_CALL_LOCK_GUARD_MUTEX()
#endif


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �C���^���N�V�����R�[�f�B�l�[�^�[ ( �C���^���N�^�[ )
// Interaction Coordinator  ( Interactor )
//
//   
// tips1.. �N���X�Ԃ̑a�����ʐM�ł���
//		   ���f�B�G�[�^�p�^�[���ƃI�u�U�[�o�[�p�^�[���̍\�z���T�|�[�g����@�\��񋟂��܂�
//
// 
// tips2.. ���̋@�\�͑a�����ʐM�������������N���X�ւ̌p����K�v�Ƃ��܂���
//         ���̂��߁A���p�҂͑a�����ʐM���K�v�ɂȂ����^�C�~���O�ł̋@�\�t�����\�ŁA�����̌p���\���ɉe����^���܂���
//         �܂��A���̋@�\�͕�܂ɂ���Ď����ł���̂Ōp���c���[�̓r���֒i�K���܂������Ă̋@�\�t�����\�ł�
// 
// 
// tips3.. ���̋@�\�𗘗p����C���X�^���X�� std::shared_ptr �ł���K�v������܂�        
//
//  
// tips4.. ���̋@�\�ɂ� ( SAFE ���[�h ) ( UNSAFE ���[�h ) �����݂��܂�
//         �@�\�����ł� dynamic_pointer_cast �� std::any_cast �Ƃ��������R�X�g�L���X�g���g�p����Ă���
//         �������������邽�߁A�^���S�����]���ɂ��č����ɓ��삷�� UNSAFE ���[�h����������Ă��܂�
//         UNSAFE ���[�h�𗘗p����ꍇ�́A���炩����( SAFE ���[�h )�œ��삷�邱�Ƃ��m�F���Ă���g�p���Ă�������
//         �� ���p�x�ȒʐM��K�v�Ƃ��Ȃ����� UNSAFE ���[�h �𗘗p����ׂ��ł͂���܂���
//
// 
// tips5.. ���̋@�\�ɂ� ���[�U�[�����ڃR�[�����Ă͂Ȃ�Ȃ��֐��E�}�N�������݂��A�����͈ȉ��̒ʂ�ł�
//         tnlInteractorNotUserCall_ �Ŏn�܂�֐�
//         TNL_INTERACTOR_NOT_USER_CALL_ �Ŏn�܂�}�N��
//         
//  
//   
// -------------------------------------------------------------------------------------------------------------------------------------------
// TNL_INTERACTOR_DECLARE �}�N��
//		�E���N���X�ւ̒ʒm�@�\��t�^�������N���X�̃����o�ɐ錾���܂�
//		�E���̃}�N���ւ̈����͒ʒm�֐��ւ̃A�N�Z�X�萔�ƂȂ�A�C�ӂ̖��O�̒萔���όŐݒ�ł��܂�
//		�E�ʒm�֐��ւ̃A�N�Z�X�萔�͓����� enum class eTnlICId �^�̃p�����[�^�ƂȂ�܂�
// 
// �� )
//	class Foo {
//	public:
//		Foo(){}
//
//		// �ʒm�@�\��t�^
//		// Foo �����N���X( Bar, Qux )�ւ̒ʒm���s�����߂� ID ��ݒ�
//		TNL_INTERACTOR_DECLARE(
//			CASE_BAR_NOTICE,
//			CASE_QUX_NOTICE_A,
//			CASE_QUX_NOTICE_B
//		); 
// 
//	} ;
// 
// -------------------------------------------------------------------------------------------------------------------------------------------
// TNL_INTERACTOR_TRANSMITTER_REGISTER �}�N��	
//		�Etips1.. �ʒm�@�\��t�^�����C���X�^���X�֒ʒm�֐���o�^���܂� ( �ʒm�֐��ֈ�����t�^���Ȃ��^�C�v�ł� )
//		�Etips2.. ���̃}�N���ɂ���Đݒ肳�ꂽ�ʒm�֐��� tnlInteractorTransmitter ���g�p���ăA�N�Z�X���܂�
//		�Earg1... �ʒm�@�\��t�^����C���X�^���X ( �|�C���^ )
//		�Earg2... �ʒm�֐��̖߂�l�̌^ ( void �w����� )
//		�Earg3... TNL_INTERACTOR_DECLARE �֔C�ӂɐݒ肵���萔�ŁA�����ʒm�֐��ւ� ID �Ƃ��܂�
//		�Earg4... �ʒm�֐��ŎQ�Ƃ����Q�ƃI�u�W�F�N�g( std::weak_ptr ���� )
//		�Earg5... �ʒm���e { } �ň͂��������ŏ������������܂�( �����_���̓������������̂݋L�q���Ă������� )
//				  { } �����ł� TNL_INTERACTOR_GET_WEAK_REFERENCE �}�N���𗘗p���Ēʒm��I�u�W�F�N�g�ւ� std::weak_ptr �����p�ł��܂�
// 
// �� )
// 
// std::shared_ptr<Foo> foo ;
// std::shared_ptr<Bar> bar ;
// 
// void main(){
//		foo = std::make_shared<Foo>() ;
//		bar = std::make_shared<Bar>() ;
// 
//		TNL_INTERACTOR_TRANSMITTER_REGISTER(foo, int, Foo::eTnlICId::CASE_BAR_NOTICE, Weak<Bar>(bar), {
//			Shared<Bar> ref_bar = TNL_INTERACTOR_GET_WEAK_REFERENCE(Bar).lock();
//			if(!ref_bar) return 0 ;
// 
//			/* �C�ӂ̏��� */
// 
//			// arg2 �� int �^���w�肵���̂� �ʒm�֐��� int�^�߂�l��Ԃ�
//			return 10 ;
//		});
// 
// }
// 
// �� TNL_INTERACTOR_UNSAFE_TRANSMITTER_REGISTER �����݂�
//    ��������g�p����� UNSAFE ���[�h �ɂȂ�܂��A�g�����͓����ł�
// 
// 
// -------------------------------------------------------------------------------------------------------------------------------------------
// TNL_INTERACTOR_ARGS_TRANSMITTER_REGISTER �}�N��
//		�Etips1.. �ʒm�@�\��t�^�����C���X�^���X�֒ʒm�֐���o�^���܂� ( �ʒm�֐��ֈ�����t�^����^�C�v�ł� )
//		�Etips2.. ���̃}�N���ɂ���Đݒ肳�ꂽ�ʒm�֐��� tnlInteractorArgsTransmitter ���g�p���ăA�N�Z�X���܂�
//		�Earg1... �ʒm�@�\��t�^����C���X�^���X ( �|�C���^ )
//		�Earg2... �ʒm�֐��̖߂�l�̌^ ( void �w����� )
//		�Earg3... TNL_INTERACTOR_DECLARE �֔C�ӂɐݒ肵���萔�ŁA�����ʒm�֐��ւ� ID �Ƃ��܂�
//		�Earg4... �ʒm�֐��ŎQ�Ƃ����Q�ƃI�u�W�F�N�g( std::weak_ptr ���� )
//		�Earg5... �ʒm�֐��̈����ɐݒ肷��C�ӂ̌^
//		�Earg6... �ʒm���e { } �ň͂��������ŏ������������܂�( �����_���̓������������̂݋L�q���Ă������� )
//				  { } �����ł� TNL_INTERACTOR_GET_WEAK_REFERENCE �}�N���𗘗p���Ēʒm��I�u�W�F�N�g�ւ� std::weak_ptr �����p�ł��܂�
//				  { } �����ł� TNL_INTERACTOR_GET_RECEIPT_INFORMATION �}�N���𗘗p���ČĂяo��������n���ꂽ�C�ӌ^�̃f�[�^�𓾂��܂�
//
// �� )
// 
// std::shared_ptr<Foo> foo ;
// std::shared_ptr<Bar> bar ;
// 
// void main(){
//		foo = std::make_shared<Foo>() ;
//		bar = std::make_shared<Bar>() ;
// 
//		TNL_INTERACTOR_ARGS_TRANSMITTER_REGISTER(foo, void, Foo::eTnlICId::CASE_BAR_NOTICE, Weak<Bar>(bar), bool, {
//			Shared<Bar> ref_bar = TNL_INTERACTOR_GET_WEAK_REFERENCE(Bar).lock();
//			if(!ref_bar) return ;
// 
//			// �����ł� arg5 �� bool �Ȃ̂� tnlInteractorArgsTransmitter �ɓn���ꂽ bool �^�p�����[�^�𓾂��܂�
//			bool receipt = TNL_INTERACTOR_GET_RECEIPT_INFORMATION() ;
// 
// 
//			/* �C�ӂ̏��� */
// 
// 
//			/* arg2 �� void �Ȃ̂Ŗ߂�l���� */
//		});
// 
// }
// 
// �� TNL_INTERACTOR_UNSAFE_ARGS_TRANSMITTER_REGISTER �����݂�
//    ��������g�p����� UNSAFE ���[�h �ɂȂ�܂��A�g�����͓����ł�
// 		
// 
// -------------------------------------------------------------------------------------------------------------------------------------------
// TNL_INTERACTOR_GET_WEAK_REFERENCE �}�N��
//		�Etips1.. �ʒm�������Œʒm��I�u�W�F�N�g�� std::weak_ptr �𓾂��܂�
//		�Etips2.. TNL_INTERACTOR_****_TRANSMITTER_REGISTER �̍Ō�ɋL�q�����ʒm�������ŗ��p�ł���}�N���ł�
//		�Earg1... �ʒm��I�u�W�F�N�g�̌^
//		�Eret.... �ʒm��I�u�W�F�N�g�� std::weak_ptr
// 
// �g�p��� TNL_INTERACTOR_TRANSMITTER_REGISTER ���Q��
// 
// 
// -------------------------------------------------------------------------------------------------------------------------------------------
// TNL_INTERACTOR_GET_RECEIPT_INFORMATION �}�N��
//		�Etips1.. �ʒm������n���ꂽ�C�ӌ^�̃f�[�^�𓾂��܂�
//		�Etips2.. TNL_INTERACTOR_****_TRANSMITTER_REGISTER �̍Ō�ɋL�q�����ʒm�������ŗ��p�ł���}�N���ł�
//
// �g�p��� TNL_INTERACTOR_ARGS_TRANSMITTER_REGISTER ���Q��
//  
// 
// -------------------------------------------------------------------------------------------------------------------------------------------
// tnlInteractorTransmitter< ReturnType > �֐� 
//		�Etips1.. �ʒm�@�\��t�^�����N���X�֎�����`�����e���v���[�g�֐��ł�
//		�Etips2.. ID �o�^����Ă���ʒm�֐��փA�N�Z�X���A���̃C���X�^���X�֒ʒm���s���܂�
//		�Etips3.. ReturnType �ɂ͒ʒm�֐�����̖߂�l�^���w�肵�܂�
//      �@�@�@�@�@�߂�l�^�� TNL_INTERACTOR_****_TRANSMITTER_REGISTER �� arg2 �Ɠ������̂��w�肷��K�v������܂�
// 
//		�Earg1... ���s����ʒm�֐��ւ̃A�N�Z�X�萔 ( eTnlICId �^ )
//		�Eret.... �ʒm��������̕ԐM�l ReturnType �^
// 
// �� )
// 
// std::shared_ptr<Foo> foo ;
// std::shared_ptr<Bar> bar ;
// 
// void main(){
//		foo = std::make_shared<Foo>() ;
//		bar = std::make_shared<Bar>() ;
// 
//		// arg2 �� int �^�ł��邱�Ƃɒ���
//		TNL_INTERACTOR_ARGS_TRANSMITTER_REGISTER(foo, int, Foo::eTnlICId::CASE_BAR_NOTICE, Weak<Bar>(bar) {
// 
//			/* ���� */
// 
//			// �ʒm�����̌��ʂƂ��� 100 ��Ԃ�
//			return 100 ;
//		});
// 
//		// �e���v���[�g������ int �^�ł��邱�Ƃɒ���
//		// value �ɂ͒ʒm�����̌��ʂƂ��� 100 ����������
//		int value = foo->tnlInteractorTransmitter<int>(Foo::eTnlICId::CASE_BAR_NOTICE) ;
// 
// }
// 
// -------------------------------------------------------------------------------------------------------------------------------------------
// tnlInteractorArgsTransmitter< ReturnType, ArgType > �֐�
//		�Etips1.. �ʒm�@�\��t�^�����N���X�֎�����`�����e���v���[�g�֐��ł�
//		�Etips2.. ID �o�^����Ă���ʒm�֐��փA�N�Z�X���A���̃C���X�^���X�֒ʒm���s���܂�
//		�Etips3.. ReturnType �ɂ͒ʒm�֐�����̖߂�l�^���w�肵�܂�
//      �@�@�@�@�@�߂�l�^�� TNL_INTERACTOR_****_TRANSMITTER_REGISTER �� arg2 �Ɠ������̂��w�肷��K�v������܂�
//		�Etips4.. ArgType �ɂ͒ʒm��ւ̕t�����Ƃ��ė^�������^���w�肵�܂�
//  
//		�Earg1... ���s����ʒm�֐��ւ̃A�N�Z�X�萔 ( eTnlICId �^ )
//		�Earg2... �ʒm��֑���C�ӌ^�f�[�^ ( ArgType )
//		�Eret.... �ʒm��������̕ԐM�l ReturnType �^
// 
// �� )
// 
// std::shared_ptr<Foo> foo ;
// std::shared_ptr<Bar> bar ;
// 
// void main(){
//		foo = std::make_shared<Foo>() ;
//		bar = std::make_shared<Bar>() ;
// 
//		// arg5 �� bool �^�ł��邱�Ƃɒ���
//		// tnlInteractorArgsTransmitter �� arg2 �Ɏw�肳���^�Ɠ����ɂ��Ă�������
//		TNL_INTERACTOR_ARGS_TRANSMITTER_REGISTER(foo, void, Foo::eTnlICId::CASE_BAR_NOTICE, Weak<Bar>(bar), bool, {
// 
//			/* ���� */
// 
//		});
// 
//		// �P�߂̃e���v���[�g�^�w��� void ��ݒ肷�邱�ƂŖ߂�l�Ȃ��̒ʒm���\
//		// �Q�߂̃e���v���[�g�^�w��� bool ��ݒ肵�����Ƃ� true or false ��t�����Ƃ��đ���܂�
//		// arg2 �� true ��t�����Ƃ��Ēʒm�����s
//		foo->tnlInteractorArgsTransmitter<void, bool>(Foo::eTnlICId::CASE_BAR_NOTICE, true) ;
// 
// }
// 
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// 
// [ �I�u�U�[�o�[�I�Ȏg�p�� ]
// 
// // Foo �� Example �ɊĎ������T�u�W�F�N�g
//class Foo {
//public:
//	Foo() {}
//
//	// �I�u�U�[�o�[( Example ) �ւ̒ʒm�C���^���N�^�[
//	TNL_INTERACTOR_DECLARE(
//		CASE_EXAMPLE_NOTICE
//	);
//
//	void setValue(int v) { value_ = v; }
//
//	void update();
//
//private:
//	float value_ = 0;
//};
// 
// 
// // Bar �� Example �ɊĎ������T�u�W�F�N�g
//class Bar {
//public:
//	Bar() {}
//
//	// �I�u�U�[�o�[( Example ) �ւ̒ʒm�C���^���N�^�[
//	TNL_INTERACTOR_DECLARE(
//		CASE_EXAMPLE_NOTICE
//	);
//
//	void setValue(int v) { value_ = v; }
//
//	void update();
//
//private:
//	int value_ = 0;
//};
//
// 
// 
// // Example ���I�u�U�[�o�[�Ƃ���
// // Foo �� Bar �̊Ď���
// class Example : public std::enable_shared_from_this<Example> {
// public :
//		Example() = default ;
// 
//		// �x���R���X�g���N�^�[��z��
//		void lazyConstruct(){
//			foo = std::make_shared<Foo>() ;
//			bar = std::make_shared<Bar>() ;
//
//			// foo �C���X�^���X���� Example �C���X�^���X�ւ̒ʒm��o�^
//			// foo ����󂯎�������� Example �� bar �𑀍�
//			TNL_INTERACTOR_ARGS_TRANSMITTER_REGISTER(foo, void, Foo::eTnlICId::CASE_EXAMPLE_NOTICE, Weak<Example>(shared_from_this()), float, {
//				Shared<Example> example = TNL_INTERACTOR_GET_WEAK_REFERENCE(Example).lock();
//				example->bar->setValue( TNL_INTERACTOR_GET_RECEIPT_INFORMATION() ) ;
//			});
//
//			// bar �C���X�^���X���� Example �C���X�^���X�ւ̒ʒm��o�^
//			// bar ����󂯎�������� Example �� foo �𑀍�
//			TNL_INTERACTOR_ARGS_TRANSMITTER_REGISTER(bar, void, Bar::eTnlICId::CASE_EXAMPLE_NOTICE, Weak<Example>(shared_from_this()), float, {
//				Shared<Example> example = TNL_INTERACTOR_GET_WEAK_REFERENCE(Example).lock();
//				example->foo->setValue( TNL_INTERACTOR_GET_RECEIPT_INFORMATION() ) ;
//			});
//		}
// 
//		std::shared_ptr<Foo> foo = nullptr ;
//		std::shared_ptr<Bar> bar = nullptr ;
// } ;
// 
// 
// 
// void Foo::update(){
// 
//		// Example �ɑ΂��� 100.0f ��ʒm
//		tnlInteractorArgsTransmitter<void, float>( eTnlICId::CASE_EXAMPLE_NOTICE, 100.0f );
// 
// }
// 
// 
// void Bar::update(){
// 
//		// Example �ɑ΂��� 200.0f ��ʒm
//		tnlInteractorArgsTransmitter<void, float>( eTnlICId::CASE_EXAMPLE_NOTICE, 200.0f );
// 
// }
// 
// 
// std::shared_ptr<Example> example = nullptr ;
// 
// void main(){
// 
//		example = std::make_shared<Example>() ;
//		example->lazyConstruct() ; // foo bar �Ƃ��� value �� 0
// 
//		example->foo->update() ;	// foo �ɂ�� example �ɒʒm������� bar vlaue �� 200.0f �ɂȂ�
//		example->bar->update() ;	// bar �ɂ�� example �ɒʒm������� foo vlaue �� 100.0f �ɂȂ�
// 
// }
// 
// 
// 
//---------------------------------------------------------------------------------------------------------------
// 
// [ ���f�B�G�[�^�I�Ȏg�p�� ]
//		����� Foo -> Bar �̒ʐM�̂ݎ��� ( �o�����ւ������ꍇ�� TNL_INTERACTOR_DECLARE �� Bar �ł��L�q )
// 
// 
//class Foo {
//public:
//	Foo() {}
//
//	// Bar �Ƃ̌�M�C���^���N�^�[
//	TNL_INTERACTOR_DECLARE(
//		CASE_BAR_NOTICE
//	);
//
//	void setValue(int v) { value_ = v; }
//
//private:
//	float value_ = 0;
//};
//
//
//class Bar {
//public:
//	Bar() {}
//
//	void setValue(int v) { value_ = v; }
//
//private:
//	int value_ = 0;
//};
//
//
//std::shared_ptr<Foo> foo = nullptr;
//std::shared_ptr<Bar> bar = nullptr;
//
//void gameStart() {
//
//	foo = std::make_shared<Foo>();
//	bar = std::make_shared<Bar>();
//
//	// foo ����󂯎�������� bar �����M�̏����X�V
//	TNL_INTERACTOR_ARGS_TRANSMITTER_REGISTER(foo, void, Foo::eTnlICId::CASE_BAR_NOTICE, Weak<Bar>(bar), float, {
//		Shared<Bar> ref_bar = TNL_INTERACTOR_GET_WEAK_REFERENCE(Bar).lock();
//		ref_bar->setValue( TNL_INTERACTOR_GET_RECEIPT_INFORMATION() );
//	});
//
//
//	// foo ���� bar �֒ʒm bar value �� 100.0f �ɕω�
//	foo->tnlInteractorArgsTransmitter<void, float>(Foo::eTnlICId::CASE_BAR_NOTICE, 100.0f);
//
//}
// 
// 
//



namespace tnl {

	class Interactor : public std::enable_shared_from_this<Interactor> {
	public:
		enum class eSafetyMode {
			SAFETY,
			UNSAFETY
		};
		Interactor() = default;
		virtual ~Interactor() {}

		template<class T>
		T getReference() {
			if (eSafetyMode::UNSAFETY == e_safety_) {
				return (*(T*)(unsafe_reference_.get()));
			}
			return std::any_cast<T>(reference_);
		}

		void setSafetyMode(eSafetyMode safety_cast) noexcept { e_safety_ = safety_cast ; }
		eSafetyMode getSafetyMode() const noexcept { return e_safety_; }

	protected :
		eSafetyMode e_safety_ = eSafetyMode::SAFETY;
		std::any reference_;
		std::unique_ptr<void, decltype(&free)> unsafe_reference_ = std::unique_ptr<void, decltype(&free)>(nullptr, free);
	};

	template<class ReturnType>
	class ConcreteInteractor final : public Interactor {
	public:
		ConcreteInteractor
		    ( const std::function<ReturnType(const Shared<Interactor>&)>& transmitter
			, const std::any& reference )
			: transmitter_(std::move(transmitter))
		{
			reference_ = reference;
		}
		ConcreteInteractor
		    ( const std::function<ReturnType(const Shared<Interactor>&)>& transmitter
			, void* unsafe_reference )
			: transmitter_(std::move(transmitter))
		{
			unsafe_reference_ = std::unique_ptr<void, decltype(&free)>(unsafe_reference, free);
		}

		~ConcreteInteractor() {}

		template<class T>
		T contact() { return transmitter_(shared_from_this()); }
		template<>
		void contact() { transmitter_(shared_from_this()); }

	private:
		std::function<ReturnType(const Shared<Interactor>&)> transmitter_;
	};

	template<class ReturnType, class ArgType>
	class ConcreteArgumentInteractor final : public Interactor {
	public:
		ConcreteArgumentInteractor
		    ( const std::function<ReturnType(const Shared<Interactor>&, ArgType)>& transmitter
			, const std::any& reference )
			: transmitter_(std::move(transmitter))
		{
			reference_ = reference;
		}
		ConcreteArgumentInteractor
		    ( const std::function<ReturnType(const Shared<Interactor>&, ArgType)>& transmitter
			, void* unsafe_reference )
			: transmitter_(std::move(transmitter))
			
		{
			unsafe_reference_ = std::unique_ptr<void, decltype(&free)>(unsafe_reference, free);
		}

		~ConcreteArgumentInteractor() {}

		template<class T>
		T contact(ArgType receipt_information) { return transmitter_(shared_from_this(), receipt_information); }
		template<>
		void contact(ArgType receipt_information) { transmitter_(shared_from_this(), receipt_information); }

	private:
		std::function<ReturnType(const Shared<Interactor>&, ArgType)> transmitter_;
	};


	#define TNL_INTERACTOR_TRANSMITTER_REGISTER( instance, return_type, e_tnl_icid, weak_ref_object, transmitter ){												\
		TNL_INTERACTOR_NOT_USER_CALL_TRANSMITTER_REGISTER_WEAK_CHECK(weak_ref_object) ;																								\
		instance->tnlInteractorNotUserCall_TransmitterRegister<return_type>( e_tnl_icid, weak_ref_object, [](const Shared<tnl::Interactor>& interactor)->return_type transmitter ) ;	\
	}

	#define TNL_INTERACTOR_ARGS_TRANSMITTER_REGISTER( instance, return_type, e_tnl_icid, weak_ref_object, send_object_type, transmitter ){								\
		TNL_INTERACTOR_NOT_USER_CALL_TRANSMITTER_REGISTER_WEAK_CHECK(weak_ref_object) ;																								\
		instance->tnlInteractorNotUserCall_ArgsTransmitterRegister<return_type, send_object_type>( e_tnl_icid, weak_ref_object, [](const Shared<tnl::Interactor>& interactor, send_object_type receipt_information)->return_type transmitter ) ;\
	}

	#define TNL_INTERACTOR_UNSAFE_TRANSMITTER_REGISTER( instance, return_type, e_tnl_icid, weak_ref_object, transmitter ){											\
		TNL_INTERACTOR_NOT_USER_CALL_TRANSMITTER_REGISTER_WEAK_CHECK(weak_ref_object) ;																								\
		auto object = weak_ref_object ;																																	\
		size_t size = sizeof(object);																																	\
		void* unsafe_reference = malloc(size);																															\
		memcpy(unsafe_reference, &object, size);																														\
		instance->tnlInteractorNotUserCall_UnsafeTransmitterRegister<return_type>( e_tnl_icid, unsafe_reference, [](const Shared<tnl::Interactor>& interactor)->return_type transmitter ) ;	\
		instance->tnlInteractorNotUserCall_SetSafetyMode(e_tnl_icid, tnl::Interactor::eSafetyMode::UNSAFETY) ;															\
	}

	#define TNL_INTERACTOR_UNSAFE_ARGS_TRANSMITTER_REGISTER( instance, return_type, e_tnl_icid, weak_ref_object, send_object_type, transmitter ){						\
		TNL_INTERACTOR_NOT_USER_CALL_TRANSMITTER_REGISTER_WEAK_CHECK(weak_ref_object) ;																								\
		auto object = weak_ref_object ;																																	\
		size_t size = sizeof(object);																																	\
		void* unsafe_reference = malloc(size);																															\
		memcpy(unsafe_reference, &object, size);																														\
		instance->tnlInteractorNotUserCall_UnsafeArgsTransmitterRegister<return_type, send_object_type>( e_tnl_icid, unsafe_reference, [](const Shared<tnl::Interactor>& interactor, send_object_type receipt_information)->return_type transmitter ) ;\
		instance->tnlInteractorNotUserCall_SetSafetyMode(e_tnl_icid, tnl::Interactor::eSafetyMode::UNSAFETY) ;															\
	}

	#define TNL_INTERACTOR_GET_WEAK_REFERENCE(ref_type) interactor->getReference<ref_type>()

	#define TNL_INTERACTOR_GET_RECEIPT_INFORMATION() receipt_information



#define TNL_INTERACTOR_DECLARE(...)					\
public :											\
	enum class eTnlICId {							\
		__VA_ARGS__									\
		, TNL_ICID_MAX								\
	};												\
private :																																								\
	std::vector<Shared<tnl::Interactor>> tnl_interactors_ = std::vector<Shared<tnl::Interactor>>( static_cast<uint32_t>(eTnlICId::TNL_ICID_MAX) );						\
	mutable std::mutex interactor_mutex_;																																\
	template<class TnlReturnType>																																		\
	void getConcreteInteractor(Shared<tnl::ConcreteInteractor<TnlReturnType>>& medi, eTnlICId e_tnl_icid) const {														\
		{																																								\
			TNL_INTERACTOR_NOT_USER_CALL_LOCK_GUARD_MUTEX();  																														\
			Shared<tnl::Interactor> interactor = tnl_interactors_[static_cast<uint32_t>(e_tnl_icid)] ;																	\
			if (tnl::Interactor::eSafetyMode::UNSAFETY == interactor->getSafetyMode() ){																				\
				medi = static_pointer_cast<tnl::ConcreteInteractor<TnlReturnType>>(interactor);																			\
			}																																							\
			else {																																						\
				medi = dynamic_pointer_cast<tnl::ConcreteInteractor<TnlReturnType>>(interactor);																		\
			}																																							\
		}																																								\
		if (medi) return ;																																				\
		tnl::DebugTrace("tnlInteractorTransmitter error : [ %s ] dynamic pointer cast mismatch \n", typeid(TnlReturnType).name());									\
		throw std::runtime_error("tnlInteractorTransmitter error : dynamic pointer cast mismatch");																	\
	}																																									\
	template<class TnlReturnType, class TnlArgType>																														\
	void getConcreteArgumentInteractor(Shared<tnl::ConcreteArgumentInteractor<TnlReturnType, TnlArgType>>& medi, eTnlICId e_tnl_icid ) const {				\
		{																																								\
			TNL_INTERACTOR_NOT_USER_CALL_LOCK_GUARD_MUTEX() ;  																										\
			Shared<tnl::Interactor> interactor = tnl_interactors_[static_cast<uint32_t>(e_tnl_icid)] ;																	\
			if (tnl::Interactor::eSafetyMode::UNSAFETY == interactor->getSafetyMode() ){																				\
				medi = static_pointer_cast<tnl::ConcreteArgumentInteractor<TnlReturnType, TnlArgType>>(interactor);														\
			}																																							\
			else {																																						\
				medi = dynamic_pointer_cast<tnl::ConcreteArgumentInteractor<TnlReturnType, TnlArgType>>(interactor);													\
			}																																							\
		}																																								\
		if (medi) return ;																																				\
		tnl::DebugTrace("tnlInteractorArgsTransmitter error : [ return type %s ] [ argument type %s ] dynamic pointer cast mismatch \n", typeid(TnlReturnType).name(), typeid(TnlArgType).name());	\
		throw std::runtime_error("tnlInteractorArgsTransmitter error : dynamic pointer cast mismatch");																	\
	}																																									\
public :																																								\
	template<class TnlReturnType = void>																																		\
	TnlReturnType tnlInteractorTransmitter( eTnlICId e_tnl_icid ) const {																							\
		Shared<tnl::ConcreteInteractor<TnlReturnType>> medi = nullptr ;																									\
		getConcreteInteractor<TnlReturnType>(medi, e_tnl_icid) ;																										\
		if constexpr (std::is_void_v<TnlReturnType>) {																													\
			medi->contact<void>();																																		\
		}																																								\
		else {																																							\
			return medi->contact<TnlReturnType>();																														\
		}																																								\
	}																																									\
	template<class TnlReturnType, class TnlArgType>																													\
	TnlReturnType tnlInteractorArgsTransmitter(eTnlICId e_tnl_icid, TnlArgType argument) const {																		\
		Shared<tnl::ConcreteArgumentInteractor<TnlReturnType, TnlArgType>> medi = nullptr ;																			\
 		getConcreteArgumentInteractor<TnlReturnType, TnlArgType>(medi, e_tnl_icid) ;																			\
		if constexpr (std::is_void_v<TnlReturnType>) {																													\
			medi->contact<void>(argument);																																\
		}																																								\
		else {																																							\
			return medi->contact<TnlReturnType>(argument);																												\
		}																																								\
	}																																									\
	/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/ \
	/*																																								 */	\
	/* �ȉ����[�U�[�ɂ�钼�ڃR�[���͋֎~ */																															\
	/*																																								 */	\
	/*---------------------------------------------------------------------------------------------------------------------------------------------------------------*/ \
	void tnlInteractorNotUserCall_SetSafetyMode( eTnlICId e_tnl_icid, tnl::Interactor::eSafetyMode cast_mode ){															\
        TNL_INTERACTOR_NOT_USER_CALL_LOCK_GUARD_MUTEX() ;   																											\
		tnl_interactors_[static_cast<uint32_t>(e_tnl_icid)]->setSafetyMode( cast_mode ) ;																				\
	}																																									\
	template< class TnlReturnType >																																	\
	void tnlInteractorNotUserCall_TransmitterRegister(eTnlICId e_tnl_icid, const std::any& reference, const std::function<TnlReturnType(const Shared<tnl::Interactor>&)>& transmitter) {		\
		Shared<tnl::ConcreteInteractor<TnlReturnType>> interactor = std::make_shared<tnl::ConcreteInteractor<TnlReturnType>>(std::move(transmitter), reference);		\
        TNL_INTERACTOR_NOT_USER_CALL_LOCK_GUARD_MUTEX() ;   																											\
		tnl_interactors_[static_cast<uint32_t>(e_tnl_icid)] = interactor ;																								\
	}																																									\
	template< class TnlReturnType, class TnlArgType >																													\
	void tnlInteractorNotUserCall_ArgsTransmitterRegister(eTnlICId e_tnl_icid, const std::any& reference, const std::function<TnlReturnType(const Shared<tnl::Interactor>&, TnlArgType)>& transmitter) {						\
		Shared<tnl::ConcreteArgumentInteractor<TnlReturnType, TnlArgType>> interactor = std::make_shared<tnl::ConcreteArgumentInteractor<TnlReturnType, TnlArgType>>(std::move(transmitter), reference);		\
        TNL_INTERACTOR_NOT_USER_CALL_LOCK_GUARD_MUTEX() ;  																											\
		tnl_interactors_[static_cast<uint32_t>(e_tnl_icid)] = interactor ;																								\
	}																																									\
	template< class TnlReturnType >																																	\
	void tnlInteractorNotUserCall_UnsafeTransmitterRegister(eTnlICId e_tnl_icid, void* reference, const std::function<TnlReturnType(const Shared<tnl::Interactor>&)>& transmitter) {		\
		Shared<tnl::ConcreteInteractor<TnlReturnType>> interactor = std::make_shared<tnl::ConcreteInteractor<TnlReturnType>>(std::move(transmitter), reference);		\
        TNL_INTERACTOR_NOT_USER_CALL_LOCK_GUARD_MUTEX() ;   																											\
		tnl_interactors_[static_cast<uint32_t>(e_tnl_icid)] = interactor ;																								\
	}																																									\
	template< class TnlReturnType, class TnlArgType >																													\
	void tnlInteractorNotUserCall_UnsafeArgsTransmitterRegister(eTnlICId e_tnl_icid, void* reference, const std::function<TnlReturnType(const Shared<tnl::Interactor>&, TnlArgType)>& transmitter) {							\
		Shared<tnl::ConcreteArgumentInteractor<TnlReturnType, TnlArgType>> interactor = std::make_shared<tnl::ConcreteArgumentInteractor<TnlReturnType, TnlArgType>>(std::move(transmitter), reference);		\
        TNL_INTERACTOR_NOT_USER_CALL_LOCK_GUARD_MUTEX() ;   																											\
		tnl_interactors_[static_cast<uint32_t>(e_tnl_icid)] = interactor ;																								\
	}																																									\

	#define TNL_INTERACTOR_NOT_USER_CALL_TRANSMITTER_REGISTER_WEAK_CHECK(weak_ref_object) {																							\
		if(!tnl::IsWeakPointer(weak_ref_object)){																														\
			tnl::DebugTrace("TNL_INTERACTOR_REGISTER error : [ %s ] is not weak pointer \n", #weak_ref_object);															\
			throw std::runtime_error("TNL_INTERACTOR_REGISTER error : argument is not weak pointer");																	\
		}																																								\
	}

}

