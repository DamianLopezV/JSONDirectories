#include <iostream>
#include <filesystem>
#include <json/json.h>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

ofstream fout("dir.json");

Json::Value directoryJSON(string dir) {
    Json::Value path;
    for (const auto& file : fs::directory_iterator(dir)) {
        if (fs::is_directory(file)) {
            Json::Value res = directoryJSON(file.path().string());
            path.append(res);
        }
        else {
            Json::Value data;
            data["name"] = file.path().filename().string();
            data["size"] = fs::file_size(file);
            path.append(data);
        }
    }

    Json::Value file;
    file[dir] = path;
    return file;
}

int main() {

    string dir = "C:\\Users\\Usuario\\Downloads\\Parcial02";

    Json::Value path;
    for (const auto& file : fs::directory_iterator(dir)) {
        if (fs::is_directory(file)) {
            Json::Value res = directoryJSON(file.path().string());
            path.append(res);
        }
        else {
            Json::Value data;
            data["name"] = file.path().filename().string();
            data["size"] = fs::file_size(file);
            path.append(data);
        }
    }

    Json::Value json;
    json["files"] = path;
    fout << json;

}