#include <sstream>
#include <fstream>

#include "struct.h"
#include "util.h"


Graph read_struct() {
    std::fstream fs;
    fs.open("../struct.txt", std::fstream::in);

    std::string line;
    Graph nodes;
    std::vector<MasterNode *> lv;

    while (std::getline(fs, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string p1, p2, p3;
        iss >> p1 >> p2;
        std::getline(iss, p3);

        size_t delimeter = p1.find(':');
        if (p1.substr(0, delimeter) == "script") {
            std::string name = p1.substr(delimeter + 1, p1.length() - 1);
            // предполагается, что все имена уникальны и проверка не требуется
            nodes.name_dict[name] = nodes.adjacency_list.size();
            nodes.adjacency_list.emplace_back(new Script{
                    name,
                    parse_string_list(p2.substr(p2.find(':') + 1, p2.length() - 1)),
                    trim_code(p3)
            });
        } else if (p1.substr(0, delimeter) == "transform") {
            std::string name = p1.substr(delimeter + 1, p1.length() - 1);
            nodes.name_dict[name] = nodes.adjacency_list.size();
            nodes.adjacency_list.emplace_back(new Transform{
                    name,
                    parse_string_list(p2.substr(p2.find(':') + 1, p2.length() - 1)),
                    trim_code(p3)
            });
        } else if (p1.substr(0, delimeter) == "wait") {
            std::string name = p1.substr(delimeter + 1, p1.length() - 1);
            nodes.name_dict[name] = nodes.adjacency_list.size();
            nodes.adjacency_list.emplace_back(new Wait{
                    name,
                    parse_string_list(p2.substr(p2.find(':') + 1, p2.length() - 1)),
                    std::stoi(p3)
            });
        } else std::cerr << "INPUT ERROR\n";

    }
    fs.close();

    return nodes;
}

void put_instructions(Graph &g) {
    std::fstream fs;
    fs.open("../data.txt", std::fstream::in);
    std::string line;

    while (std::getline(fs, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string id, names;
        iss >> id;
        std::getline(iss, names);
        const auto &list_names = parse_string_list(names, ' ');
        for (const auto &name : list_names) {
            if (name.empty()) continue;
            g.adjacency_list[g.name_dict[name]]->add_instruction(id);
        }
    }

    fs.close();
}

void put_structure_to_files(const Graph &g) {
    std::fstream fs_struct, fs_data;
    fs_struct.open("../struct_upd.txt", std::fstream::out);

    std::map<std::string, std::vector<std::string>> m;
    for (const auto &el : g.adjacency_list) {
        fs_struct << el->format_node_info() << '\n';

        for (const auto &i : el->get_instructions()) {
            if (m.find(i) != m.end()) {
                m[i].push_back(el->get_name());
            } else {
                m[i] = {el->get_name()};
            }
        }
    }
    fs_struct.close();

    fs_data.open("../data_upd.txt", std::fstream::out);
    for (const auto &i : m) {
        fs_data << i.first << ' ' << vec_to_string(i.second) << '\n';
    }
    fs_data.close();
}

int main() {
    auto v = read_struct();
    std::cout << "nodes number =  " << v.adjacency_list.size() << std::endl;

    put_instructions(v);
    for (auto el : v.adjacency_list) {
        el->print_node_info();
    }

    put_structure_to_files(v);

    return 0;
}