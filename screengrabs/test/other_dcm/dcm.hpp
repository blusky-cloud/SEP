#ifndef __DCM_H__
#define __DCM_H__
#include <iostream>
#include "../../model/include/sep/models.hpp"
#include <vector>
#include <memory>
#include "wrap.hpp"

struct Entity
{
    //virtual void Update (double elapsed_time) = 0;
};

class DCM : public Entity
{
    public:
        DCM()
        { 
            dcap_ = new sep::DeviceCapability;
            sep::Resource *edev = new sep::EndDevice;
            sep::Resource *sdev = new sep::SelfDevice;
            resource_pool_.emplace_back(dcap_);
            resource_pool_.emplace_back(edev);
            resource_pool_.emplace_back(sdev);
            
            DCapResource dcapR(dcap_);
            sep::DeviceCapability real_sep_dcap;
            DCapResource dcapR_2(real_sep_dcap);
            
            resource_objects_.emplace_back(&dcapR);
            resource_objects_.emplace_back(&dcapR_2);
            
            for (auto resource : resource_objects_)
            {
                if ( resource->poll_rate() )
                    std::cout << "the poll rate here is: " << resource->poll_rate() << std::endl;
            }
            
        };
        ~DCM()
        {
        };
        void OtherUpdate()
        {
            
            for (auto resource : resource_objects_)
            {
                if ( resource->poll_rate() )
                    std::cout << "the poll rate here is: " << resource->poll_rate() << std::endl;
            }
        }
        void Update (double elapsed_time)
        { /*
            for (auto resource : resource_pool_)
            {
                std::cout << elapsed_time << std::endl;
                if ( resource->type_info == "dCap" )
                {
                    resource->poll_rate = 1111;
                    std::cout << resource->poll_rate << std::endl;
                    //sep::DeviceCapability *dcap2 = dynamic_cast<sep::DeviceCapability*>(resource);
                    //std::cout << dcap2->poll_rate << std::endl;
                }
                if ( sep::DeviceCapability *dcap = dynamic_cast<sep::DeviceCapability*>(resource) ) 
                {
                    dcap->poll_rate = 9000;
                    sep::DeviceCapability *dcap2 = dynamic_cast<sep::DeviceCapability*>(resource);
                    std::cout << dcap2->poll_rate << "    AND NOW FOR THE WHOLE RESOURCE: " << std::endl;
                    //std::cout << *dcap2 << std::endl;
                } 
                else if (sep::EndDevice *edev = dynamic_cast<sep::EndDevice*>(resource))
                {
                    edev->changed_time = 6000;
                } 
                else if (sep::SelfDevice *sdev = dynamic_cast<sep::SelfDevice*>(resource))
                {
                    sdev->poll_rate = 3000;
                }
                else
                {
                    std::cout << "Cannot be dynamic cast" << std::endl;
                }
                */
        }
    protected:
        std::vector<sep::Resource*> resource_pool_;
        std::vector<DCMBaseResource*> resource_objects_;
        sep::Resource *dcap_;
};



namespace der
{

} // namespace der

#endif // __DCM_H__