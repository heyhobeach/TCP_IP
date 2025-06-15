
#include <iostream>
#include <filesystem>
#include <string>
namespace fs = std::filesystem;

//순서
//1 부모 먼저 주석 풀고 실행
//2 부모 주석 걸로 자식 실행

std::string RenameIf(std::string& path) {

	size_t t = path.find('.', 0);

	if (t != std::string::npos) {
		return path.substr(t + 1);
	}
	return path;

}

int main() {
	fs::path p("E:/heyhobeach/트위터/DIP_202411");
	fs::directory_iterator itr(p);

	int count = 0;

	for (const auto& entry : fs::directory_iterator(p)) {
		count++;
	}
	std::cout << count << '\n';



	for (int i = 0; i < count;i ++) {

		//부모 

		const fs::directory_entry& entry = *itr;
		/*
		std::string path = entry.path().filename().string();
		std::string newname = RenameIf(path);
		newname.insert(0, "/");
		std::string newpath = entry.path().parent_path().string().append(newname);
		fs::rename(entry.path(), newpath);
		std::cout << path << '\n';
		*/



		// 자식
		
		fs::recursive_directory_iterator chitr(entry.path());
		int chcount = 0;
		for (const auto& chentry :fs::recursive_directory_iterator(entry.path())) {
			chcount++;
			//std::cout << chentry.path() << '\n';
		}
		std::cout << chcount << '\n';
		for (int j = 0; j < chcount; j++) {
			const fs::directory_entry& chentry = *chitr;
			std::string ch_path = chentry.path().string();
			std::string newname = RenameIf(ch_path);
			newname.insert(0, "/");
			std::string newpath = chentry.path().parent_path().string().append(newname);
			fs::rename(chentry.path(), newpath);
			std::cout << ch_path << '\n';
			chitr++;
		}
		
		

		itr++;
	}


}


