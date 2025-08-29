#include <sycl/detail/common.hpp>
#include <sycl/ext/intel/esimd/emu/detail/esimd_emulator_device_interface.hpp>
  
 namespace sycl {
 __SYCL_INLINE_VER_NAMESPACE(_V1) {
 namespace detail {
  
 __SYCL_EXPORT ESIMDDeviceInterface *getESIMDDeviceInterface() {
   // TODO (performance) cache the interface pointer, can make a difference
   // when calling fine-grained libCM APIs through it (like memory access in a
   // tight loop)
   void *PIOpaqueData = nullptr;
  
   try {
     PIOpaqueData =
         getPluginOpaqueData<sycl::backend::ext_intel_esimd_emulator>(nullptr);
   } catch (...) {
     std::cerr << "ESIMD EMU plugin error or not loaded - try setting "
                  "SYCL_DEVICE_FILTER=esimd_emulator:gpu environment variable"
               << std::endl;
     throw sycl::feature_not_supported();
   }
  
   ESIMDEmuPluginOpaqueData *OpaqueData =
       reinterpret_cast<ESIMDEmuPluginOpaqueData *>(PIOpaqueData);
  
   // First check if opaque data version is compatible.
   if (OpaqueData->version != ESIMD_EMULATOR_PLUGIN_OPAQUE_DATA_VERSION) {
     // NOTE: the version check should always be '!=' as layouts of different
     // versions of PluginOpaqueData is not backward compatible, unlike
     // layout of the ESIMDDeviceInterface.
  
     std::cerr << __FUNCTION__ << std::endl
               << "Opaque data returned by ESIMD Emu plugin is incompatible with"
               << "the one used in current implementation." << std::endl
               << "Returned version : " << OpaqueData->version << std::endl
               << "Required version : "
               << ESIMD_EMULATOR_PLUGIN_OPAQUE_DATA_VERSION << std::endl;
     throw feature_not_supported();
   }
   // Opaque data version is OK, can cast the 'data' field.
   ESIMDDeviceInterface *Interface =
       reinterpret_cast<ESIMDDeviceInterface *>(OpaqueData->data);
  
   // Now check that device interface version is compatible.
   if (Interface->version < ESIMD_DEVICE_INTERFACE_VERSION) {
     std::cerr << __FUNCTION__ << std::endl
               << "The device interface version provided from plug-in "
               << "library is behind required device interface version"
               << std::endl
               << "Found version : " << Interface->version << std::endl
               << "Required version :" << ESIMD_DEVICE_INTERFACE_VERSION
               << std::endl;
     throw feature_not_supported();
   }
   return Interface;
 }
 } // namespace detail
 } // __SYCL_INLINE_VER_NAMESPACE(_V1)
 } // namespace sycl
source