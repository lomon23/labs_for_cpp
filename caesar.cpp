#include <iostream>
#include <string>
#include <cctype>

class Base_Cipher {
public:
    virtual std::string encrypt(const std::string& text, const std::string& key) = 0;
    virtual std::string decrypt(const std::string& text, const std::string& key) = 0;
    virtual ~Base_Cipher() {}
};

class Caesar_Cipher : public Base_Cipher {
public:
    std::string encrypt(const std::string& text, const std::string& key) override {
        std::string result_text = "";
        int shift_val = 0;
        
        try {
            shift_val = std::stoi(key);
        } catch (...) {
            shift_val = 0;
        }
        
        for (char ch : text) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                char base_char = 'a';
                if (std::isupper(static_cast<unsigned char>(ch))) {
                    base_char = 'A';
                }
                
                int shifted_char = (ch - base_char + shift_val) % 26;
                if (shifted_char < 0) {
                    shifted_char += 26;
                }
                result_text += shifted_char + base_char;
            } else {
                result_text += ch;
            }
        }
        return result_text;
    }

    std::string decrypt(const std::string& text, const std::string& key) override {
        int shift_val = 0;
        try {
            shift_val = std::stoi(key);
        } catch (...) {
            shift_val = 0;
        }
        return encrypt(text, std::to_string(-shift_val));
    }
};

class Vigenere_Cipher : public Base_Cipher {
public:
    std::string encrypt(const std::string& text, const std::string& key) override {
        std::string clean_key = "";
        for (char c : key) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                clean_key += c;
            }
        }
        
        if (clean_key.empty()) {
            clean_key = "a";
        }

        std::string result_text = "";
        int key_index = 0;
        int key_length = clean_key.length();

        for (char ch : text) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                char base_char = 'a';
                if (std::isupper(static_cast<unsigned char>(ch))) {
                    base_char = 'A';
                }
                
                char key_char = clean_key[key_index % key_length];
                char key_base = 'a';
                if (std::isupper(static_cast<unsigned char>(key_char))) {
                    key_base = 'A';
                }
                
                int shift_val = key_char - key_base;
                int shifted_char = (ch - base_char + shift_val) % 26;
                
                if (shifted_char < 0) {
                    shifted_char += 26;
                }
                result_text += shifted_char + base_char;
                key_index++;
            } else {
                result_text += ch;
            }
        }
        return result_text;
    }

    std::string decrypt(const std::string& text, const std::string& key) override {
        std::string clean_key = "";
        for (char c : key) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                clean_key += c;
            }
        }
        
        if (clean_key.empty()) {
            clean_key = "a";
        }

        std::string result_text = "";
        int key_index = 0;
        int key_length = clean_key.length();

        for (char ch : text) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                char base_char = 'a';
                if (std::isupper(static_cast<unsigned char>(ch))) {
                    base_char = 'A';
                }
                
                char key_char = clean_key[key_index % key_length];
                char key_base = 'a';
                if (std::isupper(static_cast<unsigned char>(key_char))) {
                    key_base = 'A';
                }
                
                int shift_val = key_char - key_base;
                int shifted_char = (ch - base_char - shift_val) % 26;
                
                if (shifted_char < 0) {
                    shifted_char += 26;
                }
                result_text += shifted_char + base_char;
                key_index++;
            } else {
                result_text += ch;
            }
        }
        return result_text;
    }
};

int main() {
    std::cout << "Select cypher:\n1 - Caesar\n2 - Vigenere\n> ";
    int cipher_choice;
    std::cin >> cipher_choice;

    if (cipher_choice != 1 && cipher_choice != 2) {
        std::cout << "Invalid cypher choice.\n";
        return 1;
    }

    std::cout << "Do you want to cypher (1) or decypher (2)\n> ";
    int action_choice;
    std::cin >> action_choice;

    if (action_choice != 1 && action_choice != 2) {
        std::cout << "Invalid action choice.\n";
        return 1;
    }

    std::cin.ignore(); 

    std::cout << "Message: ";
    std::string input_message;
    std::getline(std::cin, input_message);

    std::cout << "Key: ";
    std::string input_key;
    std::getline(std::cin, input_key);

    Base_Cipher* selected_cipher = nullptr;
    
    if (cipher_choice == 1) {
        selected_cipher = new Caesar_Cipher();
    } else {
        selected_cipher = new Vigenere_Cipher();
    }

    std::string output_result = "";

    if (action_choice == 1) {
        output_result = selected_cipher->encrypt(input_message, input_key);
    } else {
        output_result = selected_cipher->decrypt(input_message, input_key);
    }

    std::cout << "Cypher: " << output_result << "\n";

    delete selected_cipher;
    return 0;
}