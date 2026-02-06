#include<CL/sycl.hpp>
#include<iostream>
#include<vector>
#include<string>
using namespace cl::sycl;
using namespace std;

int main()
{
    auto platformlist = platform::get_platforms();
    int i=1;
    for(auto p : platformlist)
    {
       // decltype(p.get_devices(info::device_type::all)) devicelist;
        
        cout << "\n\nPlatform "<<i<<"\n";
        
        cout << "\nPlatform name: "  <<p.get_info<info::platform::name>() << "\n";
        cout << "Platform vendor: "  <<p.get_info<info::platform::vendor>() << "\n";
        cout << "Platform version: " <<p.get_info<info::platform::version>() << "\n";
        
        int j=1;
        auto devicelist = p.get_devices();
        for(auto d : devicelist)
        {
            cout << "\n\nDevice "<<j<< " in Platform "<<i<<"\n\n";
            
            cout << "Device name: "     << d.get_info<info::device::name>()    << "\n";
            cout << "Device vendor: "   << d.get_info<info::device::vendor>()  << "\n";
            cout << "Device version: "  << d.get_info<info::device::version>() << "\n";
            
            //cout << "is_host(): "       << (d.is_host() ? "Yes" : "No") << "\n";           // deprecated in 2023.0
            cout << "is_cpu(): "        << (d.is_cpu()  ? "Yes" : "No") << "\n";
            cout << "is_gpu(): "        << (d.is_gpu()  ? "Yes" : "No") << "\n";
            cout << "is_accelerator(): "<< (d.is_accelerator() ? "Yes" : "No") << "\n";
            
            cout << "Device max compute units: " <<d.get_info<info::device::max_compute_units>() << "\n";
            cout << "Device local mem size: "    <<d.get_info<info::device::local_mem_size>() << "\n";
            cout << "Device driver version: "    <<d.get_info<info::device::driver_version>() << "\n";
            cout << "Device max work group size: "       <<d.get_info<info::device::max_work_group_size>() << "\n";
            //cout << "Device supported sub-group size: "  <<d.get_info<info::device::sub_group_sizes>()<<"\n";
            cout << "Device max work item dimensions: "  <<d.get_info<info::device::max_work_item_dimensions>() << "\n";
            cout << "Device mem base addr align "        <<d.get_info<info::device::mem_base_addr_align>() << "\n";
            cout << "Device partition max sub devices : "<<d.get_info<info::device::partition_max_sub_devices>() << "\n";
            
            cout << "  - Floating point support: \n";
            cout << "      Half precision: " << d.has(sycl::aspect::fp16) << "\n";
            //cout << "      Single precision: " << d.has(sycl::aspect::fp32) << "\n";
            cout << "      Double precision: " << d.has(sycl::aspect::fp64) << "\n";
            cout << "d.has(aspect::image): "  <<d.has(aspect::image) << "\n";
            cout << "d.get_info<info::device::image_support>(): "  <<d.get_info<info::device::image_support>() << "\n";
            
            //cl_device_id clDeviceID = d.get_native<cl_device_id>();
            //cl_device_id clDeviceID = get_native<cl::sycl::backend::opencl>(d);
            //cout << "d.get_native<cl_device_id>(): "  <<d.get_native<cl_device_id>() << "\n";
            //cout << "uuid: "     << d.get_info<info::device::ext_intel_device_info_uuid>() <<"\n";
           
            j=j+1;
            
        }
        i=i+1;
    }
    return 0;
}
