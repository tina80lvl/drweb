//
// Created by  Valentina Smirnova on 9/28/21.
//
#include "struct.h"

MasterNode::MasterNode(const std::string &n, const std::vector<std::string> &v) : name(std::move(n)),
                                                                                  parents(std::move(v)) {};

std::string MasterNode::print_parents() {
    std::string s;
    for (auto p: this->parents) {
        s += p + ",";
    }
    s.pop_back();
    return s;
}

void MasterNode::print_instructions() {
    for (const auto &i: this->instructions) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void MasterNode::add_instruction(const std::string &instr) {
    instructions.emplace_back(instr);
}

std::vector<std::string> MasterNode::get_instructions() { return instructions; };

void MasterNode::print_node_info() {
    std::cout << "🥲\n";
};

std::string MasterNode::format_node_info() {
    std::cout << "🥲\n";
    return "";
}

std::string MasterNode::get_name() {
    return name;
};


Script::Script(const std::string &n, const std::vector<std::string> &v, const std::string &code) : MasterNode(n, v),
                                                                                                   code(std::move(
                                                                                                           code)) {};

void Script::print_node_info() {
    std::cout << "Script.name = " << Script::get_name() << "\nScript.parents = " <<
              this->print_parents() << '\n' << "Script.code = " << this->code << "\nScript.instructions = ";
    this->print_instructions();
    std::cout << std::endl;
}

std::string Script::format_node_info() {
    return "script:" + Script::get_name() + " parents:" + this->print_parents() + " {" + this->code + '}';
}


Transform::Transform(const std::string &n, const std::vector<std::string> &v, const std::string &rule) : MasterNode(n,
                                                                                                                    v),
                                                                                                         rule(std::move(
                                                                                                                 rule)) {};

void Transform::print_node_info() {
    std::cout << "Transform.name = " << Transform::get_name() << "\nTransform.parents = " <<
              this->print_parents() << '\n' << "Transform.rule = " << this->rule << "\nTransform.instructions = ";
    this->print_instructions();
    std::cout << std::endl;
};

std::string Transform::format_node_info() {
    return "transform:" + Transform::get_name() + " parents:" + this->print_parents() + " {" + this->rule + '}';
}


Wait::Wait(const std::string &n, const std::vector<std::string> &v, const int s) : MasterNode(n, v), sec(s) {};

void Wait::print_node_info() {
    std::cout << "Wait.name = " << Wait::get_name() << "\nWait.parents = " <<
              this->print_parents() << '\n' << "Wait.sec = " << this->sec << "\nWait.instructions = ";
    this->print_instructions();
    std::cout << std::endl;
};

std::string Wait::format_node_info() {
    return "wait:" + Wait::get_name() + " parents:" + this->print_parents() + ' ' + std::to_string(this->sec);
}
