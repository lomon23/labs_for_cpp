#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cctype>

int levenshtein_distance(const std::string& word_a, const std::string& word_b) {
    int len_a = word_a.size();
    int len_b = word_b.size();
    std::vector<std::vector<int>> dist_matrix(len_a + 1, std::vector<int>(len_b + 1));

    for (int i = 0; i <= len_a; ++i) {
        dist_matrix[i][0] = i;
    }
    
    for (int j = 0; j <= len_b; ++j) {
        dist_matrix[0][j] = j;
    }

    for (int i = 1; i <= len_a; ++i) {
        for (int j = 1; j <= len_b; ++j) {
            if (word_a[i - 1] == word_b[j - 1]) {
                dist_matrix[i][j] = dist_matrix[i - 1][j - 1];
            } else {
                dist_matrix[i][j] = 1 + std::min({dist_matrix[i - 1][j], dist_matrix[i][j - 1], dist_matrix[i - 1][j - 1]});
            }
        }
    }
    
    return dist_matrix[len_a][len_b];
}

std::string suggest_word(const std::string& target_word, const std::unordered_set<std::string>& dict_set) {
    std::string best_match = "";
    int min_dist = 10000;

    for (const auto& dict_word : dict_set) {
        int curr_dist = levenshtein_distance(target_word, dict_word);
        if (curr_dist < min_dist) {
            min_dist = curr_dist;
            best_match = dict_word;
        }
    }
    
    return best_match;
}

std::unordered_set<std::string> load_dict(const std::string& filename) {
    std::unordered_set<std::string> loaded_dict;
    std::ifstream input_file(filename);
    std::string file_word;
    
    if (input_file.is_open()) {
        while (input_file >> file_word) {
            loaded_dict.insert(file_word);
        }
        input_file.close();
    }
    
    return loaded_dict;
}

void save_word(const std::string& filename, const std::string& new_word) {
    std::ofstream output_file(filename, std::ios::app);
    
    if (output_file.is_open()) {
        output_file << new_word << "\n";
        output_file.close();
    }
}

int main() {
    const std::string dict_file = "dict.txt";
    std::unordered_set<std::string> main_dict = load_dict(dict_file);

    if (main_dict.empty()) {
        std::vector<std::string> base_words = {"hello", "my", "name", "is", "world", "test"};
        for (const auto& base_word : base_words) {
            main_dict.insert(base_word);
            save_word(dict_file, base_word);
        }
    }

    std::cout << "Введи текст: ";
    std::string user_input;
    std::getline(std::cin, user_input);

    std::string final_message = "";
    std::string curr_word_lower = "";
    std::string orig_word = "";

    user_input += " "; 

    for (char ch : user_input) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            curr_word_lower += std::tolower(static_cast<unsigned char>(ch));
            orig_word += ch;
        } else {
            if (!curr_word_lower.empty()) {
                if (main_dict.find(curr_word_lower) == main_dict.end()) {
                    std::string suggestion = suggest_word(curr_word_lower, main_dict);
                    
                    std::cout << "\nОбана, слова '" << orig_word << "' немає в словнику.\n";
                    if (!suggestion.empty()) {
                        std::cout << "Можливо, малось на увазі '" << suggestion << "'?\n";
                    }
                    
                    std::cout << "Обери дію:\n"
                              << "1 - Замінити на '" << suggestion << "'\n"
                              << "2 - Додати '" << curr_word_lower << "' у словник\n"
                              << "3 - Написати свій варіант\n> ";
                    
                    int choice;
                    std::cin >> choice;

                    if (choice == 1) {
                        final_message += suggestion;
                    } else {
                        if (choice == 2) {
                            main_dict.insert(curr_word_lower);
                            save_word(dict_file, curr_word_lower);
                            final_message += orig_word;
                            std::cout << "Слово додано в файл.\n";
                        } else {
                            if (choice == 3) {
                                std::string custom_word;
                                std::cout << "Введи правильне слово: ";
                                std::cin >> custom_word;
                                
                                std::string custom_lower = custom_word;
                                for (char& c : custom_lower) {
                                    c = std::tolower(static_cast<unsigned char>(c));
                                }
                                
                                main_dict.insert(custom_lower); 
                                save_word(dict_file, custom_lower);
                                final_message += custom_word;
                            }
                        }
                    }
                } else {
                    final_message += orig_word;
                }
                
                curr_word_lower = "";
                orig_word = "";
            }
            final_message += ch;
        }
    }

    if (!final_message.empty()) {
        final_message.pop_back(); 
    }

    std::cout << "\nФінальний виправлений текст: \n" << final_message << "\n";

    return 0;
}