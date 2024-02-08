#include <filesystem>
#include <json.hpp>
#include "opensplat.hpp"
#include "point_io.hpp"

namespace fs = std::filesystem;
using namespace torch::indexing;

int main(int argc, char *argv[]){
    std::string projectRoot = "banana";
    const float downScaleFactor = 2.0f;
    torch::Device device = torch::kCPU;

    if (torch::cuda::is_available()) {
        std::cout << "Using CUDA" << std::endl;
        device = torch::kCUDA;
    }else{
        std::cout << "Using CPU" << std::endl;
    }

    ns::InputData inputData = ns::inputDataFromNerfStudio(projectRoot);
    
    ns::Model m(inputData.points, device);
    m.to(device);

    std::cout << inputData.cameras[0].getIntrinsicsMatrix();
    inputData.cameras[0].loadImage(downScaleFactor);  
    std::cout << inputData.cameras[0].getIntrinsicsMatrix();
    
}