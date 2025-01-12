#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <filesystem>

//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// �w��t�H���_�[�̍\�������c���[�\���œ���N���X�ł�
//
// 
// �� )
// 
// std::shared_ptr<tnl::FolderTree> folder;
//
// void main() {
// 
//    srand(time(0));
//
//    // ���[�g�ɑ��݂��� example_folder �ȉ��̃t�H���_�\���𓾂�
//    folder = tnl::FolderTree::Analysis("example_folder");
//
//    // �t�H���_�K�w��[���D��T���ŏ���Ȃ���t�H���_������������
//    // arg1... �t�H���_���
//    // arg2... �T���̐[��
//    folder->roundup( [&]( const std::shared_ptr<tnl::FolderTree>& folder, uint32_t depth ) {
//         // �t�H���_�����o��
//         printf( "%s\n", folder->getFolderName().c_str() ); 
// 
//         // �t�H���_���̃t�@�C�������o��
//         for (auto file : folder->getFileNames()) {
//             printf( "%s\n", file.c_str() ) ;
//         }
//    });
// 
// 
// }
// 
// 


namespace tnl {

    class FolderTree final : public std::enable_shared_from_this<FolderTree> {
    public:
        FolderTree() = default;
        explicit FolderTree(const std::string& folder_name) : name_(folder_name), path_(folder_name) {}

        static std::shared_ptr<FolderTree> Analysis(const std::string& folder_path) {
            std::shared_ptr<FolderTree> folder = std::make_shared<FolderTree>(folder_path);
            Construction(folder_path, folder);
            return folder;
        }

        void roundup(const std::function<void(const std::shared_ptr<FolderTree>& folder, uint32_t depth)>& order, uint32_t depth = 0) {
            order(shared_from_this(), depth);
            for (const auto& fl : folders_) {
                fl->roundup(order, depth + 1);
            }
        }

        std::shared_ptr<FolderTree> getFolder(const std::string& folder_name) {
            std::shared_ptr<FolderTree> search;
            roundup([&](const std::shared_ptr<FolderTree>& folder, uint32_t depth) {
                if (folder->getFolderName() == folder_name) search = folder;
                });
            return search;
        }

        const std::string& getPath() const noexcept { return path_; }
        const std::string& getFolderName() const noexcept { return name_; }
        const std::vector<std::string>& getFileNames() const noexcept { return file_names_; }
        const std::vector<std::shared_ptr<FolderTree>>& getFolders() const noexcept { return folders_; }

    private:
        static void Construction(const std::string& path, std::shared_ptr<FolderTree>& folder) {

            size_t n = path.find_last_of("/");
            if (std::string::npos == n) n = 0;
            else n++;
            folder->name_ = path.substr(n, path.length() - n);
            try {
                for (const auto& entry : std::filesystem::directory_iterator(path)) {
                    // �t�@�C����
                    if (entry.is_regular_file()) {
                        folder->file_names_.emplace_back(entry.path().filename().string());
                    }
                    // �t�H���_����
                    if (entry.is_directory()) {
                        std::string analysis_path = path + "/" + entry.path().filename().string();
                        auto new_folder = std::make_shared<FolderTree>(entry.path().filename().string());
                        folder->folders_.emplace_back(new_folder);
                        new_folder->path_ = analysis_path;
                        Construction(analysis_path, new_folder);
                    }
                }
            }
            catch (const std::filesystem::filesystem_error& e) {
                std::ostringstream oss;
                oss << "tnl::FolderTree Construction Error: " << e.what();
                throw std::runtime_error(oss.str());
            }
        }

        std::string name_;
        std::string path_;
        std::vector<std::string> file_names_;
        std::vector<std::shared_ptr<FolderTree>> folders_;
    };

}




