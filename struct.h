//
// Created by  Valentina Smirnova on 9/20/21.
//

#ifndef DRWEB_STRUCT_H
#define DRWEB_STRUCT_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

#endif //DRWEB_STRUCT_H

class MasterNode {
public:
    MasterNode(const std::string &n, const std::vector<std::string> &v);

    std::string print_parents();

    void print_instructions();

    void add_instruction(const std::string &instr);

    std::vector<std::string> get_instructions();

    std::string get_name();

    virtual void print_node_info();

    virtual std::string format_node_info();

private:
    std::string name;
    std::vector<std::string> parents;
    std::vector<std::string> instructions;
};

class Script : public MasterNode {
public:
    Script(const std::string &n, const std::vector<std::string> &v, const std::string &code);

    void print_node_info() override;

    std::string format_node_info() override;

private:
    std::string code;
};

class Transform : public MasterNode {
public:
    Transform(const std::string &n, const std::vector<std::string> &v, const std::string &rule);

    void print_node_info() override;

    std::string format_node_info() override;

private:
    std::string rule;
};

class Wait : public MasterNode {
public:
    Wait(const std::string &n, const std::vector<std::string> &v, const int s);

    void print_node_info() override;

    std::string format_node_info() override;

private:
    int sec;
};

struct Graph {
    std::vector<MasterNode *> adjacency_list;
    std::map<std::string, int> name_dict;
};

