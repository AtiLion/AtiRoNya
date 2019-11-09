#pragma once

#include "InternalHelpers.hpp"

#pragma region Compiler Definitions
#define il2cpp_array_addr_with_size(_array, size, index) ( ((char*)(_array)->vector) + (size) * (index) )
#define DO_API(r, n, p) typedef r n p;
#define DO_API_NO_RETURN(r, n, p) typedef r n p;
#pragma endregion

#pragma region Import Types
typedef void (*IL2CPPMethodPointer)();
typedef void* (*IL2CPPInvokerMethod)(IL2CPPMethodPointer, const void*, void*, void**);
typedef uintptr_t il2cpp_array_size_t;
typedef wchar_t IL2CPPChar;
typedef wchar_t IL2CPPNativeChar;
typedef IL2CPPNativeChar* (*IL2CPPSetFindPlugInCallback)(IL2CPPNativeChar*);
typedef void (*IL2CPPLogCallback)(const char*);
#pragma endregion
#pragma region Import Structures
struct IL2CPPType;
struct EventInfo;
struct PropertyInfo;
struct IL2CPPAssembly;
struct IL2CPPDelegate;
struct IL2CPPDomain;
struct IL2CPPImage;
struct IL2CPPException;
struct IL2CPPProfiler;
struct IL2CPPObject;
struct IL2CPPReflectionMethod;
struct IL2CPPReflectionType;
struct IL2CPPThread;
struct IL2CPPAsyncResult;
struct IL2CPPManagedMemorySnapshot;
struct IL2CPPCustomAttrInfo;
struct IL2CPPField;
struct IL2CPPClass;
struct IL2CPPGuid;
struct IL2CPPAppDomain;
struct IL2CPPAppDomainSetup;
struct IL2CPPAppContext;
struct IL2CPPNameToTypeDefinitionIndexHashTable;
struct IL2CPPArray {
	IL2CPPObject* obj;
	void* bounds;
	uint32_t max_length;
	double vector[0];
};
struct IL2CPPString;
struct IL2CPPMethod {
	IL2CPPMethodPointer methodPointer;
};
#pragma endregion
#pragma region Import Classes
typedef enum {
	IL2CPP_UNHANDLED_POLICY_LEGACY,
	IL2CPP_UNHANDLED_POLICY_CURRENT
} IL2CPPRuntimeUnhandledExceptionPolicy;
#pragma endregion
#pragma region Import Functions
DO_API(IL2CPPDomain*, (*il2cpp_init_t), (const char* domain_name));
DO_API(IL2CPPDomain*, (*il2cpp_init_utf16_t), (IL2CPPChar* domain_name));
DO_API(void, (*il2cpp_shutdown_t), ());
DO_API(void, (*il2cpp_set_config_dir_t), (const char* config_path));
DO_API(void, (*il2cpp_set_data_dir_t), (const char* data_path));
DO_API(void, (*il2cpp_set_temp_dir_t), (const char* temp_path));
DO_API(void, (*il2cpp_set_commandline_arguments_t), (int argc, const char* const argv[], const char* basedir));
DO_API(void, (*il2cpp_set_commandline_arguments_utf16_t), (int argc, IL2CPPChar* const argv[], const char* basedir));
DO_API(void, (*il2cpp_set_config_utf16_t), (IL2CPPChar* executablePath));
DO_API(void, (*il2cpp_set_config_t), (const char* executablePath));

DO_API(IL2CPPImage*, (*il2cpp_get_corlib_t), ());
DO_API(void, (*il2cpp_add_internal_call_t), (const char* name, IL2CPPMethodPointer method));
DO_API(IL2CPPMethodPointer, (*il2cpp_resolve_icall_t), (const char* name));

DO_API(void*, (*il2cpp_alloc_t), (size_t size));
DO_API(void, (*il2cpp_free_t), (void* ptr));

// array
DO_API(IL2CPPClass*, (*il2cpp_array_class_get_t), (IL2CPPClass* element_class, uint32_t rank));
DO_API(uint32_t, (*il2cpp_array_length_t), (IL2CPPArray* array));
DO_API(uint32_t, (*il2cpp_array_get_byte_length_t), (IL2CPPArray* array));
DO_API(IL2CPPArray*, (*il2cpp_array_new_t), (IL2CPPClass* elementTypeInfo, il2cpp_array_size_t length));
DO_API(IL2CPPArray*, (*il2cpp_array_new_specific_t), (IL2CPPClass* arrayTypeInfo, il2cpp_array_size_t length));
DO_API(IL2CPPArray*, (*il2cpp_array_new_full_t), (IL2CPPClass* array_class, il2cpp_array_size_t* lengths, il2cpp_array_size_t* lower_bounds));
DO_API(IL2CPPClass*, (*il2cpp_bounded_array_class_get_t), (IL2CPPClass* element_class, uint32_t rank, bool bounded));
DO_API(int, (*il2cpp_array_element_size_t), (IL2CPPClass* array_class));

// assembly
DO_API(IL2CPPImage*, (*il2cpp_assembly_get_image_t), (IL2CPPAssembly* assembly));

// class
DO_API(IL2CPPType*, (*il2cpp_class_enum_basetype_t), (IL2CPPClass* klass));
DO_API(bool, (*il2cpp_class_is_generic_t), (IL2CPPClass* klass));
DO_API(bool, (*il2cpp_class_is_inflated_t), (IL2CPPClass* klass));
DO_API(bool, (*il2cpp_class_is_assignable_from_t), (IL2CPPClass* klass, IL2CPPClass* oklass));
DO_API(bool, (*il2cpp_class_is_subclass_of_t), (IL2CPPClass* klass, IL2CPPClass* klassc, bool check_interfaces));
DO_API(bool, (*il2cpp_class_has_parent_t), (IL2CPPClass* klass, IL2CPPClass* klassc));
DO_API(IL2CPPClass*, (*il2cpp_class_from_il2cpp_type_t), (IL2CPPType* type));
DO_API(IL2CPPClass*, (*il2cpp_class_from_name_t), (IL2CPPImage* image, const char* namespaze, const char* name));
DO_API(IL2CPPClass*, (*il2cpp_class_from_system_type_t), (IL2CPPReflectionType* type));
DO_API(IL2CPPClass*, (*il2cpp_class_get_element_class_t), (IL2CPPClass* klass));
DO_API(const EventInfo*, (*il2cpp_class_get_events_t), (IL2CPPClass* klass, void** iter));
DO_API(IL2CPPField*, (*il2cpp_class_get_fields_t), (IL2CPPClass* klass, void** iter));
DO_API(IL2CPPClass*, (*il2cpp_class_get_nested_types_t), (IL2CPPClass* klass, void** iter));
DO_API(IL2CPPClass*, (*il2cpp_class_get_interfaces_t), (IL2CPPClass* klass, void** iter));
DO_API(const PropertyInfo*, (*il2cpp_class_get_properties_t), (IL2CPPClass* klass, void** iter));
DO_API(const PropertyInfo*, (*il2cpp_class_get_property_from_name_t), (IL2CPPClass* klass, const char* name));
DO_API(IL2CPPField*, (*il2cpp_class_get_field_from_name_t), (IL2CPPClass* klass, const char* name));
DO_API(IL2CPPMethod*, (*il2cpp_class_get_methods_t), (IL2CPPClass* klass, void** iter));
DO_API(IL2CPPMethod*, (*il2cpp_class_get_method_from_name_t), (IL2CPPClass* klass, const char* name, int argsCount));
DO_API(const char*, (*il2cpp_class_get_name_t), (IL2CPPClass* klass));
DO_API(const char*, (*il2cpp_class_get_namespace_t), (IL2CPPClass* klass));
DO_API(IL2CPPClass*, (*il2cpp_class_get_parent_t), (IL2CPPClass* klass));
DO_API(IL2CPPClass*, (*il2cpp_class_get_declaring_type_t), (IL2CPPClass* klass));
DO_API(int32_t, (*il2cpp_class_instance_size_t), (IL2CPPClass* klass));
DO_API(uint32_t, (*il2cpp_class_num_fields_t), (IL2CPPClass* enumKlass));
DO_API(bool, (*il2cpp_class_is_valuetype_t), (IL2CPPClass* klass));
DO_API(int32_t, (*il2cpp_class_value_size_t), (IL2CPPClass* klass, uint32_t* align));
DO_API(bool, (*il2cpp_class_is_blittable_t), (IL2CPPClass* klass));
DO_API(int, (*il2cpp_class_get_flags_t), (IL2CPPClass* klass));
DO_API(bool, (*il2cpp_class_is_abstract_t), (IL2CPPClass* klass));
DO_API(bool, (*il2cpp_class_is_interface_t), (IL2CPPClass* klass));
DO_API(int, (*il2cpp_class_array_element_size_t), (IL2CPPClass* klass));
DO_API(IL2CPPClass*, (*il2cpp_class_from_type_t), (IL2CPPType* type));
DO_API(IL2CPPType*, (*il2cpp_class_get_type_t), (IL2CPPClass* klass));
DO_API(uint32_t, (*il2cpp_class_get_type_token_t), (IL2CPPClass* klass));
DO_API(bool, (*il2cpp_class_has_attribute_t), (IL2CPPClass* klass, IL2CPPClass* attr_class));
DO_API(bool, (*il2cpp_class_has_references_t), (IL2CPPClass* klass));
DO_API(bool, (*il2cpp_class_is_enum_t), (IL2CPPClass* klass));
DO_API(IL2CPPImage*, (*il2cpp_class_get_image_t), (IL2CPPClass* klass));
DO_API(const char*, (*il2cpp_class_get_assemblyname_t), (IL2CPPClass* klass));
DO_API(int, (*il2cpp_class_get_rank_t), (IL2CPPClass* klass));

// testing only
DO_API(size_t, (*il2cpp_class_get_bitmap_size_t), (IL2CPPClass* klass));
DO_API(void, (*il2cpp_class_get_bitmap_t), (IL2CPPClass* klass, size_t* bitmap));

// domain
DO_API(IL2CPPDomain*, (*il2cpp_domain_get_t), ());
DO_API(IL2CPPAssembly*, (*il2cpp_domain_assembly_open_t), (IL2CPPDomain* domain, const char* name));
DO_API(IL2CPPAssembly**, (*il2cpp_domain_get_assemblies_t), (IL2CPPDomain* domain, uint32_t* size));

// exception
DO_API_NO_RETURN(void, (*il2cpp_raise_exception_t), (IL2CPPException*));
DO_API(IL2CPPException*, (*il2cpp_exception_from_name_msg_t), (IL2CPPImage* image, const char* name_space, const char* name, const char* msg));
DO_API(IL2CPPException*, (*il2cpp_get_exception_argument_null_t), (const char* arg));
DO_API(void, (*il2cpp_format_exception_t), (IL2CPPException* ex, char* message, int message_size));
DO_API(void, (*il2cpp_format_stack_trace_t), (IL2CPPException* ex, char* output, int output_size));
DO_API(void, (*il2cpp_unhandled_exception_t), (IL2CPPException*));

// field
DO_API(int, (*il2cpp_field_get_flags_t), (IL2CPPField* field));
DO_API(const char*, (*il2cpp_field_get_name_t), (IL2CPPField* field));
DO_API(IL2CPPClass*, (*il2cpp_field_get_parent_t), (IL2CPPField* field));
DO_API(size_t, (*il2cpp_field_get_offset_t), (IL2CPPField* field));
DO_API(IL2CPPType*, (*il2cpp_field_get_type_t), (IL2CPPField* field));
DO_API(void, (*il2cpp_field_get_value_t), (IL2CPPObject* obj, IL2CPPField* field, void* value));
DO_API(IL2CPPObject*, (*il2cpp_field_get_value_object_t), (IL2CPPField* field, IL2CPPObject* obj));
DO_API(bool, (*il2cpp_field_has_attribute_t), (IL2CPPField* field, IL2CPPClass* attr_class));
DO_API(void, (*il2cpp_field_set_value_t), (IL2CPPObject* obj, IL2CPPField* field, void* value));
DO_API(void, (*il2cpp_field_static_get_value_t), (IL2CPPField* field, void* value));
DO_API(void, (*il2cpp_field_static_set_value_t), (IL2CPPField* field, void* value));
DO_API(void, (*il2cpp_field_set_value_object_t), (IL2CPPObject* instance, IL2CPPField* field, IL2CPPObject* value));

// gc
DO_API(void, (*il2cpp_gc_collect_t), (int maxGenerations));
DO_API(int32_t, (*il2cpp_gc_collect_a_little_t), ());
DO_API(void, (*il2cpp_gc_disable_t), ());
DO_API(void, (*il2cpp_gc_enable_t), ());
DO_API(bool, (*il2cpp_gc_is_disabled_t), ());
DO_API(int64_t, (*il2cpp_gc_get_used_size_t), ());
DO_API(int64_t, (*il2cpp_gc_get_heap_size_t), ());
DO_API(void, (*il2cpp_gc_wbarrier_set_field_t), (IL2CPPObject* obj, void** targetAddress, void* object));

// gchandle
DO_API(uint32_t, (*il2cpp_gchandle_new_t), (IL2CPPObject* obj, bool pinned));
DO_API(uint32_t, (*il2cpp_gchandle_new_weakref_t), (IL2CPPObject* obj, bool track_resurrection));
DO_API(IL2CPPObject*, (*il2cpp_gchandle_get_target_t), (uint32_t gchandle));
DO_API(void, (*il2cpp_gchandle_free_t), (uint32_t gchandle));

// method
DO_API(IL2CPPType*, (*il2cpp_method_get_return_type_t), (IL2CPPMethod* method));
DO_API(IL2CPPClass*, (*il2cpp_method_get_declaring_type_t), (IL2CPPMethod* method));
DO_API(const char*, (*il2cpp_method_get_name_t), (IL2CPPMethod* method));
DO_API(IL2CPPMethod*, (*il2cpp_method_get_from_reflection_t), (IL2CPPReflectionMethod* method));
DO_API(IL2CPPReflectionMethod*, (*il2cpp_method_get_object_t), (IL2CPPMethod* method, IL2CPPClass* refclass));
DO_API(bool, (*il2cpp_method_is_generic_t), (IL2CPPMethod* method));
DO_API(bool, (*il2cpp_method_is_inflated_t), (IL2CPPMethod* method));
DO_API(bool, (*il2cpp_method_is_instance_t), (IL2CPPMethod* method));
DO_API(uint32_t, (*il2cpp_method_get_param_count_t), (IL2CPPMethod* method));
DO_API(IL2CPPType*, (*il2cpp_method_get_param_t), (IL2CPPMethod* method, uint32_t index));
DO_API(IL2CPPClass*, (*il2cpp_method_get_class_t), (IL2CPPMethod* method));
DO_API(bool, (*il2cpp_method_has_attribute_t), (IL2CPPMethod* method, IL2CPPClass* attr_class));
DO_API(uint32_t, (*il2cpp_method_get_flags_t), (IL2CPPMethod* method, uint32_t* iflags));
DO_API(uint32_t, (*il2cpp_method_get_token_t), (IL2CPPMethod* method));
DO_API(const char*, (*il2cpp_method_get_param_name_t), (IL2CPPMethod* method, uint32_t index));

// property
DO_API(uint32_t, (*il2cpp_property_get_flags_t), (PropertyInfo* prop));
DO_API(IL2CPPMethod*, (*il2cpp_property_get_get_method_t), (PropertyInfo* prop));
DO_API(IL2CPPMethod*, (*il2cpp_property_get_set_method_t), (PropertyInfo* prop));
DO_API(const char*, (*il2cpp_property_get_name_t), (PropertyInfo* prop));
DO_API(IL2CPPClass*, (*il2cpp_property_get_parent_t), (PropertyInfo* prop));

// object
DO_API(IL2CPPClass*, (*il2cpp_object_get_class_t), (IL2CPPObject* obj));
DO_API(uint32_t, (*il2cpp_object_get_size_t), (IL2CPPObject* obj));
DO_API(IL2CPPMethod*, (*il2cpp_object_get_virtual_method_t), (IL2CPPObject* obj, IL2CPPMethod* method));
DO_API(IL2CPPObject*, (*il2cpp_object_new_t), (IL2CPPClass* klass));
DO_API(void*, (*il2cpp_object_unbox_t), (IL2CPPObject* obj));

DO_API(IL2CPPObject*, (*il2cpp_value_box_t), (IL2CPPClass* klass, void* data));

// monitor
DO_API(void, (*il2cpp_monitor_enter_t), (IL2CPPObject* obj));
DO_API(bool, (*il2cpp_monitor_try_enter_t), (IL2CPPObject* obj, uint32_t timeout));
DO_API(void, (*il2cpp_monitor_exit_t), (IL2CPPObject* obj));
DO_API(void, (*il2cpp_monitor_pulse_t), (IL2CPPObject* obj));
DO_API(void, (*il2cpp_monitor_pulse_all_t), (IL2CPPObject* obj));
DO_API(void, (*il2cpp_monitor_wait_t), (IL2CPPObject* obj));
DO_API(bool, (*il2cpp_monitor_try_wait_t), (IL2CPPObject* obj, uint32_t timeout));

// runtime
DO_API(IL2CPPObject*, (*il2cpp_runtime_invoke_t), (IL2CPPMethod* method, void* obj, void** params, IL2CPPObject** exc));
DO_API(IL2CPPObject*, (*il2cpp_runtime_invoke_convert_args_t), (IL2CPPMethod* method, void* obj, IL2CPPObject** params, int paramCount, IL2CPPException** exc));
DO_API(void, (*il2cpp_runtime_class_init_t), (IL2CPPClass* klass));
DO_API(void, (*il2cpp_runtime_object_init_t), (IL2CPPObject* obj));

DO_API(void, (*il2cpp_runtime_object_init_exception_t), (IL2CPPObject* obj, IL2CPPException** exc));

DO_API(void, (*il2cpp_runtime_unhandled_exception_policy_set_t), (IL2CPPRuntimeUnhandledExceptionPolicy value));

// string
DO_API(int32_t, (*il2cpp_string_length_t), (IL2CPPString* str));
DO_API(IL2CPPChar*, (*il2cpp_string_chars_t), (IL2CPPString* str));
DO_API(IL2CPPString*, (*il2cpp_string_new_t), (const char* str));
DO_API(IL2CPPString*, (*il2cpp_string_new_len_t), (const char* str, uint32_t length));
DO_API(IL2CPPString*, (*il2cpp_string_new_utf16_t), (IL2CPPChar* text, int32_t len));
DO_API(IL2CPPString*, (*il2cpp_string_new_wrapper_t), (const char* str));
DO_API(IL2CPPString*, (*il2cpp_string_intern_t), (IL2CPPString* str));
DO_API(IL2CPPString*, (*il2cpp_string_is_interned_t), (IL2CPPString* str));

// thread
DO_API(IL2CPPThread*, (*il2cpp_thread_current_t), ());
DO_API(IL2CPPThread*, (*il2cpp_thread_attach_t), (IL2CPPDomain* domain));
DO_API(void, (*il2cpp_thread_detach_t), (IL2CPPThread* thread));

DO_API(IL2CPPThread**, (*il2cpp_thread_get_all_attached_threads_t), (size_t* size));
DO_API(bool, (*il2cpp_is_vm_thread_t), (IL2CPPThread* thread));

// type
DO_API(IL2CPPObject*, (*il2cpp_type_get_object_t), (IL2CPPType* type));
DO_API(int, (*il2cpp_type_get_type_t), (IL2CPPType* type));
DO_API(IL2CPPClass*, (*il2cpp_type_get_class_or_element_class_t), (IL2CPPType* type));
DO_API(char*, (*il2cpp_type_get_name_t), (IL2CPPType* type));
DO_API(bool, (*il2cpp_type_is_byref_t), (IL2CPPType* type));
DO_API(uint32_t, (*il2cpp_type_get_attrs_t), (IL2CPPType* type));
DO_API(bool, (*il2cpp_type_equals_t), (IL2CPPType* type, IL2CPPType* otherType));
DO_API(char*, (*il2cpp_type_get_assembly_qualified_name_t), (IL2CPPType* type));

// image
DO_API(IL2CPPAssembly*, (*il2cpp_image_get_assembly_t), (IL2CPPImage* image));
DO_API(const char*, (*il2cpp_image_get_name_t), (IL2CPPImage* image));
DO_API(const char*, (*il2cpp_image_get_filename_t), (IL2CPPImage* image));
DO_API(IL2CPPMethod*, (*il2cpp_image_get_entry_point_t), (IL2CPPImage* image));

DO_API(uint32_t, (*il2cpp_image_get_class_count_t), (IL2CPPImage* image));
DO_API(IL2CPPClass*, (*il2cpp_image_get_class_t), (IL2CPPImage* image, uint32_t index));

// Memory information
DO_API(IL2CPPManagedMemorySnapshot*, (*il2cpp_capture_memory_snapshot_t), ());
DO_API(void, (*il2cpp_free_captured_memory_snapshot_t), (IL2CPPManagedMemorySnapshot* snapshot));

DO_API(void, (*il2cpp_set_find_plugin_callback_t), (IL2CPPSetFindPlugInCallback method));

// Logging
DO_API(void, (*il2cpp_register_log_callback_t), (IL2CPPLogCallback method));

// Debugger
DO_API(void, (*il2cpp_debugger_set_agent_options_t), (const char* options));
DO_API(bool, (*il2cpp_is_debugger_attached_t), ());

// TLS module
DO_API(void, (*il2cpp_unity_install_unitytls_interface_t), (const void* unitytlsInterfaceStruct));

// custom attributes
DO_API(IL2CPPCustomAttrInfo*, (*il2cpp_custom_attrs_from_class_t), (IL2CPPClass* klass));
DO_API(IL2CPPCustomAttrInfo*, (*il2cpp_custom_attrs_from_method_t), (IL2CPPMethod* method));

DO_API(IL2CPPObject*, (*il2cpp_custom_attrs_get_attr_t), (IL2CPPCustomAttrInfo* ainfo, IL2CPPClass* attr_klass));
DO_API(bool, (*il2cpp_custom_attrs_has_attr_t), (IL2CPPCustomAttrInfo* ainfo, IL2CPPClass* attr_klass));
DO_API(IL2CPPArray*, (*il2cpp_custom_attrs_construct_t), (IL2CPPCustomAttrInfo* cinfo));

DO_API(void, (*il2cpp_custom_attrs_free_t), (IL2CPPCustomAttrInfo* ainfo));
#pragma endregion

#pragma region Globalize Functions
extern il2cpp_init_t il2cpp_init;
extern il2cpp_init_utf16_t il2cpp_init_utf16;
extern il2cpp_shutdown_t il2cpp_shutdown;
extern il2cpp_set_config_dir_t il2cpp_set_config_dir;
extern il2cpp_set_data_dir_t il2cpp_set_data_dir;
extern il2cpp_set_temp_dir_t il2cpp_set_temp_dir;
extern il2cpp_set_commandline_arguments_t il2cpp_set_commandline_arguments;
extern il2cpp_set_commandline_arguments_utf16_t il2cpp_set_commandline_arguments_utf16;
extern il2cpp_set_config_utf16_t il2cpp_set_config_utf16;
extern il2cpp_set_config_t il2cpp_set_config;
extern il2cpp_get_corlib_t il2cpp_get_corlib;
extern il2cpp_add_internal_call_t il2cpp_add_internal_call;
extern il2cpp_resolve_icall_t il2cpp_resolve_icall;
extern il2cpp_alloc_t il2cpp_alloc;
extern il2cpp_free_t il2cpp_free;
extern il2cpp_array_class_get_t il2cpp_array_class_get;
extern il2cpp_array_length_t il2cpp_array_length;
extern il2cpp_array_get_byte_length_t il2cpp_array_get_byte_length;
extern il2cpp_array_new_t il2cpp_array_new;
extern il2cpp_array_new_specific_t il2cpp_array_new_specific;
extern il2cpp_array_new_full_t il2cpp_array_new_full;
extern il2cpp_bounded_array_class_get_t il2cpp_bounded_array_class_get;
extern il2cpp_array_element_size_t il2cpp_array_element_size;
extern il2cpp_class_enum_basetype_t il2cpp_class_enum_basetype;
extern il2cpp_class_is_generic_t il2cpp_class_is_generic;
extern il2cpp_class_is_inflated_t il2cpp_class_is_inflated;
extern il2cpp_class_is_assignable_from_t il2cpp_class_is_assignable_from;
extern il2cpp_class_is_subclass_of_t il2cpp_class_is_subclass_of;
extern il2cpp_class_has_parent_t il2cpp_class_has_parent;
extern il2cpp_class_from_il2cpp_type_t il2cpp_class_from_il2cpp_type;
extern il2cpp_class_from_name_t il2cpp_class_from_name;
extern il2cpp_class_from_system_type_t il2cpp_class_from_system_type;
extern il2cpp_class_get_element_class_t il2cpp_class_get_element_class;
extern il2cpp_class_get_events_t il2cpp_class_get_events;
extern il2cpp_class_get_fields_t il2cpp_class_get_fields;
extern il2cpp_class_get_nested_types_t il2cpp_class_get_nested_types;
extern il2cpp_class_get_interfaces_t il2cpp_class_get_interfaces;
extern il2cpp_class_get_properties_t il2cpp_class_get_properties;
extern il2cpp_class_get_property_from_name_t il2cpp_class_get_property_from_name;
extern il2cpp_class_get_field_from_name_t il2cpp_class_get_field_from_name;
extern il2cpp_class_get_methods_t il2cpp_class_get_methods;
extern il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name;
extern il2cpp_class_get_name_t il2cpp_class_get_name;
extern il2cpp_class_get_namespace_t il2cpp_class_get_namespace;
extern il2cpp_class_get_parent_t il2cpp_class_get_parent;
extern il2cpp_class_get_declaring_type_t il2cpp_class_get_declaring_type;
extern il2cpp_class_instance_size_t il2cpp_class_instance_size;
extern il2cpp_class_num_fields_t il2cpp_class_num_fields;
extern il2cpp_class_is_valuetype_t il2cpp_class_is_valuetype;
extern il2cpp_class_value_size_t il2cpp_class_value_size;
extern il2cpp_class_is_blittable_t il2cpp_class_is_blittable;
extern il2cpp_class_get_flags_t il2cpp_class_get_flags;
extern il2cpp_class_is_abstract_t il2cpp_class_is_abstract;
extern il2cpp_class_is_interface_t il2cpp_class_is_interface;
extern il2cpp_class_array_element_size_t il2cpp_class_array_element_size;
extern il2cpp_class_from_type_t il2cpp_class_from_type;
extern il2cpp_class_get_type_t il2cpp_class_get_type;
extern il2cpp_class_get_type_token_t il2cpp_class_get_type_token;
extern il2cpp_class_has_attribute_t il2cpp_class_has_attribute;
extern il2cpp_class_has_references_t il2cpp_class_has_references;
extern il2cpp_class_is_enum_t il2cpp_class_is_enum;
extern il2cpp_class_get_image_t il2cpp_class_get_image;
extern il2cpp_class_get_assemblyname_t il2cpp_class_get_assemblyname;
extern il2cpp_class_get_rank_t il2cpp_class_get_rank;
extern il2cpp_class_get_bitmap_size_t il2cpp_class_get_bitmap_size;
extern il2cpp_class_get_bitmap_t il2cpp_class_get_bitmap;
extern il2cpp_domain_get_t il2cpp_domain_get;
extern il2cpp_domain_assembly_open_t il2cpp_domain_assembly_open;
extern il2cpp_domain_get_assemblies_t il2cpp_domain_get_assemblies;
extern il2cpp_assembly_get_image_t il2cpp_assembly_get_image;
extern il2cpp_raise_exception_t il2cpp_raise_exception;
extern il2cpp_exception_from_name_msg_t il2cpp_exception_from_name_msg;
extern il2cpp_get_exception_argument_null_t il2cpp_get_exception_argument_null;
extern il2cpp_format_exception_t il2cpp_format_exception;
extern il2cpp_format_stack_trace_t il2cpp_format_stack_trace;
extern il2cpp_unhandled_exception_t il2cpp_unhandled_exception;
extern il2cpp_field_get_flags_t il2cpp_field_get_flags;
extern il2cpp_field_get_name_t il2cpp_field_get_name;
extern il2cpp_field_get_parent_t il2cpp_field_get_parent;
extern il2cpp_field_get_offset_t il2cpp_field_get_offset;
extern il2cpp_field_get_type_t il2cpp_field_get_type;
extern il2cpp_field_get_value_t il2cpp_field_get_value;
extern il2cpp_field_get_value_object_t il2cpp_field_get_value_object;
extern il2cpp_field_has_attribute_t il2cpp_field_has_attribute;
extern il2cpp_field_set_value_t il2cpp_field_set_value;
extern il2cpp_field_static_get_value_t il2cpp_field_static_get_value;
extern il2cpp_field_static_set_value_t il2cpp_field_static_set_value;
extern il2cpp_field_set_value_object_t il2cpp_field_set_value_object;
extern il2cpp_gc_collect_t il2cpp_gc_collect;
extern il2cpp_gc_collect_a_little_t il2cpp_gc_collect_a_little;
extern il2cpp_gc_disable_t il2cpp_gc_disable;
extern il2cpp_gc_enable_t il2cpp_gc_enable;
extern il2cpp_gc_is_disabled_t il2cpp_gc_is_disabled;
extern il2cpp_gc_get_used_size_t il2cpp_gc_get_used_size;
extern il2cpp_gc_get_heap_size_t il2cpp_gc_get_heap_size;
extern il2cpp_gc_wbarrier_set_field_t il2cpp_gc_wbarrier_set_field;
extern il2cpp_gchandle_new_t il2cpp_gchandle_new;
extern il2cpp_gchandle_new_weakref_t il2cpp_gchandle_new_weakref;
extern il2cpp_gchandle_get_target_t il2cpp_gchandle_get_target;
extern il2cpp_gchandle_free_t il2cpp_gchandle_free;
extern il2cpp_method_get_return_type_t il2cpp_method_get_return_type;
extern il2cpp_method_get_declaring_type_t il2cpp_method_get_declaring_type;
extern il2cpp_method_get_name_t il2cpp_method_get_name;
extern il2cpp_method_get_from_reflection_t il2cpp_method_get_from_reflection;
extern il2cpp_method_get_object_t il2cpp_method_get_object;
extern il2cpp_method_is_generic_t il2cpp_method_is_generic;
extern il2cpp_method_is_inflated_t il2cpp_method_is_inflated;
extern il2cpp_method_is_instance_t il2cpp_method_is_instance;
extern il2cpp_method_get_param_count_t il2cpp_method_get_param_count;
extern il2cpp_method_get_param_t il2cpp_method_get_param;
extern il2cpp_method_get_class_t il2cpp_method_get_class;
extern il2cpp_method_has_attribute_t il2cpp_method_has_attribute;
extern il2cpp_method_get_flags_t il2cpp_method_get_flags;
extern il2cpp_method_get_token_t il2cpp_method_get_token;
extern il2cpp_method_get_param_name_t il2cpp_method_get_param_name;
extern il2cpp_property_get_flags_t il2cpp_property_get_flags;
extern il2cpp_property_get_get_method_t il2cpp_property_get_get_method;
extern il2cpp_property_get_set_method_t il2cpp_property_get_set_method;
extern il2cpp_property_get_name_t il2cpp_property_get_name;
extern il2cpp_property_get_parent_t il2cpp_property_get_parent;
extern il2cpp_object_get_class_t il2cpp_object_get_class;
extern il2cpp_object_get_size_t il2cpp_object_get_size;
extern il2cpp_object_get_virtual_method_t il2cpp_object_get_virtual_method;
extern il2cpp_object_new_t il2cpp_object_new;
extern il2cpp_object_unbox_t il2cpp_object_unbox;
extern il2cpp_value_box_t il2cpp_value_box;
extern il2cpp_monitor_enter_t il2cpp_monitor_enter;
extern il2cpp_monitor_try_enter_t il2cpp_monitor_try_enter;
extern il2cpp_monitor_exit_t il2cpp_monitor_exit;
extern il2cpp_monitor_pulse_t il2cpp_monitor_pulse;
extern il2cpp_monitor_pulse_all_t il2cpp_monitor_pulse_all;
extern il2cpp_monitor_wait_t il2cpp_monitor_wait;
extern il2cpp_monitor_try_wait_t il2cpp_monitor_try_wait;
extern il2cpp_runtime_invoke_t il2cpp_runtime_invoke;
extern il2cpp_runtime_invoke_convert_args_t il2cpp_runtime_invoke_convert_args;
extern il2cpp_runtime_class_init_t il2cpp_runtime_class_init;
extern il2cpp_runtime_object_init_t il2cpp_runtime_object_init;
extern il2cpp_runtime_object_init_exception_t il2cpp_runtime_object_init_exception;
extern il2cpp_runtime_unhandled_exception_policy_set_t il2cpp_runtime_unhandled_exception_policy_set;
extern il2cpp_string_length_t il2cpp_string_length;
extern il2cpp_string_chars_t il2cpp_string_chars;
extern il2cpp_string_new_t il2cpp_string_new;
extern il2cpp_string_new_len_t il2cpp_string_new_len;
extern il2cpp_string_new_utf16_t il2cpp_string_new_utf16;
extern il2cpp_string_new_wrapper_t il2cpp_string_new_wrapper;
extern il2cpp_string_intern_t il2cpp_string_intern;
extern il2cpp_string_is_interned_t il2cpp_string_is_interned;
extern il2cpp_thread_current_t il2cpp_thread_current;
extern il2cpp_thread_attach_t il2cpp_thread_attach;
extern il2cpp_thread_detach_t il2cpp_thread_detach;
extern il2cpp_thread_get_all_attached_threads_t il2cpp_thread_get_all_attached_threads;
extern il2cpp_is_vm_thread_t il2cpp_is_vm_thread;
extern il2cpp_type_get_object_t il2cpp_type_get_object;
extern il2cpp_type_get_type_t il2cpp_type_get_type;
extern il2cpp_type_get_class_or_element_class_t il2cpp_type_get_class_or_element_class;
extern il2cpp_type_get_name_t il2cpp_type_get_name;
extern il2cpp_type_is_byref_t il2cpp_type_is_byref;
extern il2cpp_type_get_attrs_t il2cpp_type_get_attrs;
extern il2cpp_type_equals_t il2cpp_type_equals;
extern il2cpp_type_get_assembly_qualified_name_t il2cpp_type_get_assembly_qualified_name;
extern il2cpp_image_get_assembly_t il2cpp_image_get_assembly;
extern il2cpp_image_get_name_t il2cpp_image_get_name;
extern il2cpp_image_get_filename_t il2cpp_image_get_filename;
extern il2cpp_image_get_entry_point_t il2cpp_image_get_entry_point;
extern il2cpp_image_get_class_count_t il2cpp_image_get_class_count;
extern il2cpp_image_get_class_t il2cpp_image_get_class;
extern il2cpp_capture_memory_snapshot_t il2cpp_capture_memory_snapshot;
extern il2cpp_free_captured_memory_snapshot_t il2cpp_free_captured_memory_snapshot;
extern il2cpp_set_find_plugin_callback_t il2cpp_set_find_plugin_callback;
extern il2cpp_register_log_callback_t il2cpp_register_log_callback;
extern il2cpp_debugger_set_agent_options_t il2cpp_debugger_set_agent_options;
extern il2cpp_is_debugger_attached_t il2cpp_is_debugger_attached;
extern il2cpp_unity_install_unitytls_interface_t il2cpp_unity_install_unitytls_interface;
extern il2cpp_custom_attrs_from_class_t il2cpp_custom_attrs_from_class;
extern il2cpp_custom_attrs_from_method_t il2cpp_custom_attrs_from_method;
extern il2cpp_custom_attrs_get_attr_t il2cpp_custom_attrs_get_attr;
extern il2cpp_custom_attrs_has_attr_t il2cpp_custom_attrs_has_attr;
extern il2cpp_custom_attrs_construct_t il2cpp_custom_attrs_construct;
extern il2cpp_custom_attrs_free_t il2cpp_custom_attrs_free;
#pragma endregion
#pragma region Custom Functions
void* il2cpp_array_get(IL2CPPArray* _array, size_t size, int index);
void il2cpp_array_set(IL2CPPArray* _array, size_t size, int index, char* obj);
#pragma endregion

void Build_IL2CPP(HMODULE hMono);