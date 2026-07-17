#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// Hàm phân tách chuỗi thành các từ (Lexer đơn giản)
std::vector<std::string> lex(const std::string& code) {
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(code);
    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Hàm thực thi Runtime xử lý cấu trúc SOV
std::string run_kplus(const std::string& code) {
    std::vector<std::string> tokens = lex(code);
    if (tokens.empty()) return "k+- Error: Khong co ma nguon.";

    std::string output = "";

    // Giả sử cấu trúc câu lệnh: [Đối tượng/Dữ liệu] [Nơi nhận] [Hành động]
    // Ví dụ cú pháp hiển thị: "Hello_World console print"
    if (tokens.size() >= 3) {
        std::string data = tokens[0];
        std::string target = tokens[1];
        std::string action = tokens[2];

        if (target == "console" && action == "print") {
            // Thay thế dấu gạch dưới thành dấu cách cho chuỗi văn bản
            for (size_t i = 0; i < data.length(); ++i) {
                if (data[i] == '_') data[i] = ' ';
            }
            output += data + "\n";
            return output;
        }
    }

    return "k+- Syntax Error: Cau truc lenh khong hop le (Yeu cau SOV).";
}

// Điểm mấu chốt để WebAssembly gọi được hàm này từ JavaScript
extern "C" {
    const char* execute_code(const char* input_code) {
        static std::string result;
        result = run_kplus(std::string(input_code));
        return result.c_str();
    }
}

int main() {
    // Chạy thử nghiệm trong console local nếu muốn
    std::cout << "k+- Core loaded." << std::endl;
    return 0;
}
