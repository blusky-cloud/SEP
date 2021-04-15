#include "ECS_dcm.hpp"



//system to print entities
void SystemPrint(flecs::iter& it, sep::FlowReservationResponse* f)
{
    for (auto i : it)
    {
        
    }
}
//ECS_DCM constructor, currently not overloaded, this is just testing stuff out
ECS_DCM::ECS_DCM() 
{
    std::cout << std::endl << "|------- ECS_DCM CONSTRUCTED ------|" << std::endl;
    //add types as components to world_, see ecs_tags.hpp 
    world_.component<sep::FlowReservationResponse>();
    world_.component<Active>();
    world_.component<Start>();
    world_.component<Duration>();
    world_.component<sep::CurrentStatus>(); //event_status.hpp
    world_.component<ActiveNow>(); //if we use a tag rather then component, we can query all "active" resources

    //world_.system<sep::FlowReservationResponse>("SystemPrint").iter(SystemPrint);
}
//destructor
ECS_DCM::~ECS_DCM()
{}
//might add too later, depending 
void ECS_DCM::PrintWholeSEPResource(sep::Resource* r)
{
    std::cout << " PRINTING THE WHOLE RESOURCE FROM A PTR "<<std::endl;
    std::cout << r->href <<std::endl;  
}
//just print every field in the whole hierarchy
void ECS_DCM::PrintWholeFlow(sep::FlowReservationResponse f)
{
    std::cout << " PRINTING THE WHOLE FLOWRES:  " << std::endl;
    
    //Resource (base)
    std::cout << "href: " << f.href << std::endl; //string, this is the field of base Resource type
    
    //Resource > RespondatbleResource
    std::cout << "resource.href: " << f.resource.href << std::endl;//it contains a resource
    std::cout << "reply_to: " << f.reply_to << std::endl; //string
    std::cout << "response_required enum: " << static_cast<std::uint8_t>(f.response_required) << std::endl; //enum
    
    //Resource > RespondatbleResource > RespondableSubscribableIdentifiedObject
    std::cout << "mrid: " << f.mrid << std::endl; //string
    std::cout << "description: " << f.description << std::endl; //string
    std::cout << "version: " << f.version << std::endl; //uint16_t
    std::cout << "subscribable enum: " << static_cast<std::uint8_t>(f.subscribable) << std::endl; //enum
    
    //Resource > RespondatbleResource > RespondableSubscribableIdentifiedObject > Event
    std::cout << "creation_time" << f.creation_time << std::endl; //TimeType, which is int64_t
    //These are from EventStatus, which is contained by event
    std::cout << "current_status enum: "; //<< static_cast<std::uint8_t>(f.event_status.current_status) << std::endl; //from enum
    if (f.event_status.current_status == sep::CurrentStatus::kActive) //I've just been using kActive for testing
        std::cout << " kActive " << std::endl;
    std::cout << "date_time: " <<  f.event_status.date_time << std::endl;
    std::cout << "potentially_superceded: " << f.event_status.potentially_superseded<< std::endl;//bool
    std::cout << "potentially_superceded_time: " << f.event_status.potentially_superseded_time << std::endl;//int64_t
    std::cout << "reason: " << f.event_status.reason << std::endl;
    //from datetimeinterval, contained by event
    std::cout << "duration: " << f.interval.duration << std::endl;
    std::cout << "start: " << f.interval.start << std::endl;

    //Resource > RespondatbleResource > RespondableSubscribableIdentifiedObject > Event > FlowReservationResponse
    //first we have the fields from SignedRealEnergy, contained by FlowResResponse
    std::cout << "energy_available multiplier: " << f.energy_available.multiplier << std::endl;
    std::cout << "energy_available value: " << f.energy_available.value << std::endl;
    //now ActivePower
    std::cout << "power_available multiplier: " << f.power_available.multiplier<< std::endl;
    std::cout << "power_available value: " << f.power_available.value<< std::endl;
    //and finally
    std::cout << "subject: " << f.subject<< std::endl;


    std::cout << " THAT WAS THE WHOLE FLOWRES " << std::endl;
}
//create a flowresresp struct from arguments
sep::FlowReservationResponse ECS_DCM::MakeFakeFlowResResp(Start num, Duration drn, sep::CurrentStatus cst)
{

    struct testing {
        int a;
        int b;
    };
    testing teststruct {1, 2};
    //std::cout << "Test struct:  " << teststruct.a << teststruct.b << " did it work " << std::endl;
    
   /* struct testing2 : testing {
        int c;
        double d;
    };
    testing2 test2 { .a=1, .b=2, .c=3, .d=4.4 };
    std::cout << "Test2 struct:  " << test2.a << test2.b 
                                   << test2.c << test2.d <<  " did it work 2" << std::endl;*/

    sep::FlowReservationResponse t;
    t.href = "example href";
    t.description = "a description";
    t.interval.start = num;
    t.interval.duration = drn;
    t.event_status.current_status = cst;

    return t;
}
//lets test some flecs prefab vibes!
void ECS_DCM::ECSPrefabTest()
{
    std::cout << "|------- ECSPrefabTest ----|"<< std::endl;
    //--------------Make a Prefab Entity with a FlowReservationResponse as one component, plus some other data
    auto FlowResRspPrefab = world_.prefab("FlowResRspPrefab")
        .add<sep::FlowReservationResponse>()
        .add<Start>() //see ecs_tags.hpp for these
        .add<Duration>()
        .add<sep::CurrentStatus>()
        .add<Active>();
    //----------create a particular instance of an sep flowres struct
    sep::FlowReservationResponse example_sep_flowres = MakeFakeFlowResResp();
    //---------pass it to a new prefab entity
    auto SingleFlowResRespEntity = world_.entity()
        .add_instanceof(FlowResRspPrefab)
        .add<sep::FlowReservationResponse>().set<sep::FlowReservationResponse>({example_sep_flowres})
        .add<Start>().set<Start>({example_sep_flowres.interval.start}) //that's the magic... built-in parsing
        .add<sep::CurrentStatus>().set<sep::CurrentStatus>({example_sep_flowres.event_status.current_status})
        .add<Active>().set<Active>({example_sep_flowres.event_status.current_status == sep::CurrentStatus::kActive});//bool for active or not, many other ways to do this

    //test a mechanism to add an active now tag based on CurrentStatus enum component state
    if ( *(SingleFlowResRespEntity.get<sep::CurrentStatus>()) == sep::CurrentStatus::kActive )
        SingleFlowResRespEntity.add<ActiveNow>(); //this works to add a tag
    
    //the ActiveNow tag could now be used in queries
    
    //--------Alright, now we have an entity made from a prefab, lets register a system and then use it
    world_.system<sep::FlowReservationResponse>("PrintFlows").iter(PrintFlows);
    world_.progress();
    
    std::cout << "|--- ECSPrefabTest OVER ---|"<< std::endl;
}