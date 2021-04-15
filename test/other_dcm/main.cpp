//#include <gtest/gtest.h>
#include "ECS_dcm.hpp"

void ECSTest(); //prototype for compiler

int main() 
{
    //DCM test_dcm;
    std::cout << "|--------- MAIN ---|" << std::endl << std::endl;
    //test_dcm.OtherUpdate;
    ECSTest(); //test some ECS stuff
}
//--------------------------------------------------------
//         Entity Component Systems - Proof of Concept
//--------------------------------------------------------
void ECSTest()
{
    std::cout<< "|------- ECSTest -----------------------------------------------|" << std::endl << std::endl;
    flecs::world world;
    ECS_DCM experiment;

    sep::FlowReservationResponse flowresp;
    //experiment.PrintWholeFlow(flowresp);
    
    flowresp = experiment.MakeFakeFlowResResp();
    experiment.ECSPrefabTest();
    
    std::cout << std::endl << "|------- ECSTest OVER -------------------------------------------|" << std::endl << std::endl;
}