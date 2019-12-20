#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

enum class Op {
    Add = 1,
    Mul = 2,
    Write = 3,
    Read = 4,
    JumpIfTrue = 5,
    JumpIfFalse = 6,
    LessThan = 7,
    Equals = 8,
    End = 99
};

int op_arity(Op op) {
    switch (op) {
        case Op::Add:         return 3;
        case Op::Mul:         return 3;
        case Op::Write:       return 1;
        case Op::Read:        return 1;
        case Op::JumpIfTrue:  return 2;
        case Op::JumpIfFalse: return 2;
        case Op::LessThan:    return 3;
        case Op::Equals:      return 3;
        case Op::End:         return -1;
    }
}

int parse_instruction(std::vector<int>& mem, int ip, Op& op, int* (&val)[3]) {
    op = static_cast<Op>(mem[ip] % 100);
    int mode_flags = mem[ip] / 100;
    const int arity = op_arity(op);
    for (int j = 0; j < arity; j++) {
        if ((mode_flags % 10) != 0) {
            val[j] = &mem[ip + j + 1];
        } else {
            val[j] = &mem[mem[ip + j + 1]];
        }
        mode_flags /= 10;
    }
    return arity + 1;
}

bool run_program(std::vector<int>& mem, int& ip, std::stack<int>& input, int& output) {
    const int N = mem.size();
    while (ip < N) {
        Op op;
        int* val[3];
        ip += parse_instruction(mem, ip, op, val);
        switch (op) {
            case Op::End: {
                return true;
            }
            case Op::Add: {
                *val[2] = *val[0] + *val[1];
                break;
            }
            case Op::Mul: {
                *val[2] = *val[0] * *val[1];
                break;
            }
            case Op::Write: {
                if (input.empty()) {
                    int i;
                    std::cin >> i;
                    input.push(i);
                }
                *val[0] = input.top();
                input.pop();
                break;
            }
            case Op::Read: {
                output = *val[0];
                return false;
            }
            case Op::JumpIfTrue: {
                if (*val[0] != 0) {
                    ip = *val[1];
                }
                break;
            }
            case Op::JumpIfFalse: {
                if (*val[0] == 0) {
                    ip = *val[1];
                }
                break;
            }
            case Op::LessThan: {
                *val[2] = *val[0] < *val[1] ? 1 : 0;
                break;
            }
            case Op::Equals: {
                *val[2] = *val[0] == *val[1] ? 1 : 0;
                break;
            }
        }
    }
    return true;
}

int amplify(const std::vector<int>& program, const std::vector<int>& phases) {
    struct Amplifier {
        std::vector<int> mem;
        int ip;
    };
    std::vector<Amplifier> amplifiers(phases.size());
    for (Amplifier& a : amplifiers) {
        a.mem = program;
        a.ip = 0;
    }
    int output = 0;
    int amp_id = 0;
    int loop_count = 0;
    std::stack<int> input;
    while (true) {
        input.push(output);
        if (loop_count < amplifiers.size()) {
            input.push(phases[amp_id]);
        }
        const bool halted = run_program(amplifiers[amp_id].mem, amplifiers[amp_id].ip, input, output);
        if (halted) {
            break;
        }
        amp_id = (amp_id + 1) % amplifiers.size();
        loop_count++;
    }
    return output;
}

int permute(const std::vector<int>& program, std::vector<int>& phases, int chosen) {
    if (chosen == phases.size()) {
        return amplify(program, phases);
    }
    int result = 0;
    for (int i = chosen; i < phases.size(); i++) {
        std::swap(phases[chosen], phases[i]);
        result = std::max(result, permute(program, phases, chosen + 1));
        std::swap(phases[chosen], phases[i]);
    }
    return result;
}

int main() {
    std::vector<int> program = {3,8,1001,8,10,8,105,1,0,0,21,38,63,88,97,118,199,280,361,442,99999,3,9,1002,9,3,9,101,2,9,9,1002,9,4,9,4,9,99,3,9,101,3,9,9,102,5,9,9,101,3,9,9,1002,9,3,9,101,3,9,9,4,9,99,3,9,1002,9,2,9,1001,9,3,9,102,3,9,9,101,2,9,9,1002,9,4,9,4,9,99,3,9,102,2,9,9,4,9,99,3,9,102,4,9,9,101,5,9,9,102,2,9,9,101,5,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,99,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,99,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,1,9,9,4,9,99,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1001,9,2,9,4,9,99};
    std::vector<int> phases = {5,6,7,8,9};
    const int result = permute(program, phases, 0);
    std::cout << result << std::endl;
    return 0;
}