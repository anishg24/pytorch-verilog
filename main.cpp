#include <iostream>
#include <torch/torch.h>

#include "Vadder.h"

int main (int argc, char *argv[]) {
    Verilated::commandArgs(argc, argv);
    auto *dut = new Vadder;

    torch::Tensor tensor = torch::randint(6, {2, 3});
    std::cout << "Tensor:" << std::endl << tensor << std::endl << std::endl;
    for (int j = 0; j < 3; ++j) {
        dut->a = tensor[0][j].item<CData>();
        dut->b = tensor[1][j].item<CData>();
        dut->eval();
        std::cout << (int) dut->a << " + " << (int) dut->b << " = " << (int) dut->c << std::endl;
    }

  return 0;
}
