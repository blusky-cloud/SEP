//#ifndef __WRAP_H__
//#define __WRAP_H__
#include <iostream>
#include "../../model/include/sep/models.hpp"
#include <vector>
#include <memory>


class DCMBaseResource {
    public:
        DCMBaseResource() {}
        virtual ~DCMBaseResource() {}
        virtual int poll_rate(int new_poll_rate) {}
        virtual std::string we_could_even_pass_pack_CSV_or_xml() {}   
        virtual void or_pass_it_in(std::string incoming) {}
};
class DCapResource : public DCMBaseResource {
    public:
        DCapResource() {}
        DCapResource(const sep::DeviceCapability & model) : dcap_model_(model) 
        {
            std::cout << "that was easy" << std::endl;
            std::cout << dcap_model_.poll_rate << std::endl;
        }
        DCapResource(sep::Resource * model)  //so we can still work with base Resource objects
        {
            if ( typeid(*model) == typeid(dcap_model_) )
            {
                std::cout << "match" << std::endl;
                sep::DeviceCapability * d = dynamic_cast<sep::DeviceCapability*>(model);
                std::cout << d->poll_rate << std::endl;
            }
        }
        int poll_rate() 
        {
            return dcap_model_.poll_rate;
        }
        std::string we_could_even_pass_pack_CSV_or_xml() {}   
        void or_pass_it_in(std::string incoming) {}
        ~DCapResource() {}
    protected:
        sep::DeviceCapability dcap_model_;
};
class EndDeviceResource : public DCMBaseResource {
    public:
        EndDeviceResource() {}
        EndDeviceResource(const sep::EndDevice & model) : end_model_(model) {}
        int poll_rate() 
        {
            return 0; //end device doesn't have a poll rate
        }
        std::string we_could_even_pass_pack_CSV_or_xml() {} 
        void or_pass_it_in(std::string incoming) {}
        ~EndDeviceResource() {}
    protected:
        sep::EndDevice end_model_;
};
class SelfDeviceResource : public DCMBaseResource {
    public:
        SelfDeviceResource() {}
        SelfDeviceResource(const sep::SelfDevice & model) : self_model_(model) {}
        int poll_rate() 
        {
            return self_model_.poll_rate;
        }
        std::string we_could_even_pass_pack_CSV_or_xml() {} 
        void or_pass_it_in(std::string incoming) {}
        ~SelfDeviceResource() {}
    protected:
        sep::SelfDevice self_model_;
};


/*class FlowResWrap : public FlowReservationResponse {
    public:
        FlowResWrap();
        FlowResWrap(const FlowResWrap &);
        ~FlowResWrap();
}
*/