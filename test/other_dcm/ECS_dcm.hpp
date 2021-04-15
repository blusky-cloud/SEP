#include "dcm.hpp" //everything else defined in here
#include "ecs_tags.hpp" //flecs defined in here


void SystemPrint();//prototype

class ECS_DCM : public DCM {
    public:
        ECS_DCM();
        ~ECS_DCM();
        void PrintWholeSEPResource(sep::Resource* r);
        void PrintWholeFlow(sep::FlowReservationResponse f);
        sep::FlowReservationResponse MakeFakeFlowResResp(Start num = 42, Duration drn = 314, sep::CurrentStatus cst = sep::CurrentStatus::kActive);
        void ECSPrefabTest();
        static void PrintFlows(flecs::iter& it, sep::FlowReservationResponse* f)
        {
            ECS_DCM dcm;
            for (auto i : it)
            {   
                dcm.PrintWholeFlow(f[i]);
            }
        }

    protected:
        flecs::world world_;
        ecs_entity_t flowres_entity_;
        Start start1_;
        Duration dur1_;
        Active actv1_;
        sep::CurrentStatus status1_;

};
