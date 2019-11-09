#include "il2cpp.h"

#pragma region Construct Functions
il2cpp_init_t il2cpp_init = NULL;
il2cpp_init_utf16_t il2cpp_init_utf16 = NULL;
il2cpp_shutdown_t il2cpp_shutdown = NULL;
il2cpp_set_config_dir_t il2cpp_set_config_dir = NULL;
il2cpp_set_data_dir_t il2cpp_set_data_dir = NULL;
il2cpp_set_temp_dir_t il2cpp_set_temp_dir = NULL;
il2cpp_set_commandline_arguments_t il2cpp_set_commandline_arguments = NULL;
il2cpp_set_commandline_arguments_utf16_t il2cpp_set_commandline_arguments_utf16 = NULL;
il2cpp_set_config_utf16_t il2cpp_set_config_utf16 = NULL;
il2cpp_set_config_t il2cpp_set_config = NULL;

il2cpp_get_corlib_t il2cpp_get_corlib = NULL;
il2cpp_add_internal_call_t il2cpp_add_internal_call = NULL;
il2cpp_resolve_icall_t il2cpp_resolve_icall = NULL;

il2cpp_alloc_t il2cpp_alloc = NULL;
il2cpp_free_t il2cpp_free = NULL;

il2cpp_array_class_get_t il2cpp_array_class_get = NULL;
il2cpp_array_length_t il2cpp_array_length = NULL;
il2cpp_array_get_byte_length_t il2cpp_array_get_byte_length = NULL;
il2cpp_array_new_t il2cpp_array_new = NULL;
il2cpp_array_new_specific_t il2cpp_array_new_specific = NULL;
il2cpp_array_new_full_t il2cpp_array_new_full = NULL;
il2cpp_bounded_array_class_get_t il2cpp_bounded_array_class_get = NULL;
il2cpp_array_element_size_t il2cpp_array_element_size = NULL;

il2cpp_class_enum_basetype_t il2cpp_class_enum_basetype = NULL;
il2cpp_class_is_generic_t il2cpp_class_is_generic = NULL;
il2cpp_class_is_inflated_t il2cpp_class_is_inflated = NULL;
il2cpp_class_is_assignable_from_t il2cpp_class_is_assignable_from = NULL;
il2cpp_class_is_subclass_of_t il2cpp_class_is_subclass_of = NULL;
il2cpp_class_has_parent_t il2cpp_class_has_parent = NULL;
il2cpp_class_from_il2cpp_type_t il2cpp_class_from_il2cpp_type = NULL;
il2cpp_class_from_name_t il2cpp_class_from_name = NULL;
il2cpp_class_from_system_type_t il2cpp_class_from_system_type = NULL;
il2cpp_class_get_element_class_t il2cpp_class_get_element_class = NULL;
il2cpp_class_get_events_t il2cpp_class_get_events = NULL;
il2cpp_class_get_fields_t il2cpp_class_get_fields = NULL;
il2cpp_class_get_nested_types_t il2cpp_class_get_nested_types = NULL;
il2cpp_class_get_interfaces_t il2cpp_class_get_interfaces = NULL;
il2cpp_class_get_properties_t il2cpp_class_get_properties = NULL;
il2cpp_class_get_property_from_name_t il2cpp_class_get_property_from_name = NULL;
il2cpp_class_get_field_from_name_t il2cpp_class_get_field_from_name = NULL;
il2cpp_class_get_methods_t il2cpp_class_get_methods = NULL;
il2cpp_class_get_method_from_name_t il2cpp_class_get_method_from_name = NULL;
il2cpp_class_get_name_t il2cpp_class_get_name = NULL;
il2cpp_class_get_namespace_t il2cpp_class_get_namespace = NULL;
il2cpp_class_get_parent_t il2cpp_class_get_parent = NULL;
il2cpp_class_get_declaring_type_t il2cpp_class_get_declaring_type = NULL;
il2cpp_class_instance_size_t il2cpp_class_instance_size = NULL;
il2cpp_class_num_fields_t il2cpp_class_num_fields = NULL;
il2cpp_class_is_valuetype_t il2cpp_class_is_valuetype = NULL;
il2cpp_class_value_size_t il2cpp_class_value_size = NULL;
il2cpp_class_is_blittable_t il2cpp_class_is_blittable = NULL;
il2cpp_class_get_flags_t il2cpp_class_get_flags = NULL;
il2cpp_class_is_abstract_t il2cpp_class_is_abstract = NULL;
il2cpp_class_is_interface_t il2cpp_class_is_interface = NULL;
il2cpp_class_array_element_size_t il2cpp_class_array_element_size = NULL;
il2cpp_class_from_type_t il2cpp_class_from_type = NULL;
il2cpp_class_get_type_t il2cpp_class_get_type = NULL;
il2cpp_class_get_type_token_t il2cpp_class_get_type_token = NULL;
il2cpp_class_has_attribute_t il2cpp_class_has_attribute = NULL;
il2cpp_class_has_references_t il2cpp_class_has_references = NULL;
il2cpp_class_is_enum_t il2cpp_class_is_enum = NULL;
il2cpp_class_get_image_t il2cpp_class_get_image = NULL;
il2cpp_class_get_assemblyname_t il2cpp_class_get_assemblyname = NULL;
il2cpp_class_get_rank_t il2cpp_class_get_rank = NULL;
il2cpp_class_get_bitmap_size_t il2cpp_class_get_bitmap_size = NULL;
il2cpp_class_get_bitmap_t il2cpp_class_get_bitmap = NULL;

il2cpp_domain_get_t il2cpp_domain_get = NULL;
il2cpp_domain_assembly_open_t il2cpp_domain_assembly_open = NULL;
il2cpp_domain_get_assemblies_t il2cpp_domain_get_assemblies = NULL;
il2cpp_assembly_get_image_t il2cpp_assembly_get_image = NULL;

il2cpp_raise_exception_t il2cpp_raise_exception = NULL;
il2cpp_exception_from_name_msg_t il2cpp_exception_from_name_msg = NULL;
il2cpp_get_exception_argument_null_t il2cpp_get_exception_argument_null = NULL;
il2cpp_format_exception_t il2cpp_format_exception = NULL;
il2cpp_format_stack_trace_t il2cpp_format_stack_trace = NULL;
il2cpp_unhandled_exception_t il2cpp_unhandled_exception = NULL;

il2cpp_field_get_flags_t il2cpp_field_get_flags = NULL;
il2cpp_field_get_name_t il2cpp_field_get_name = NULL;
il2cpp_field_get_parent_t il2cpp_field_get_parent = NULL;
il2cpp_field_get_offset_t il2cpp_field_get_offset = NULL;
il2cpp_field_get_type_t il2cpp_field_get_type = NULL;
il2cpp_field_get_value_t il2cpp_field_get_value = NULL;
il2cpp_field_get_value_object_t il2cpp_field_get_value_object = NULL;
il2cpp_field_has_attribute_t il2cpp_field_has_attribute = NULL;
il2cpp_field_set_value_t il2cpp_field_set_value = NULL;
il2cpp_field_static_get_value_t il2cpp_field_static_get_value = NULL;
il2cpp_field_static_set_value_t il2cpp_field_static_set_value = NULL;
il2cpp_field_set_value_object_t il2cpp_field_set_value_object = NULL;

il2cpp_gc_collect_t il2cpp_gc_collect = NULL;
il2cpp_gc_collect_a_little_t il2cpp_gc_collect_a_little = NULL;
il2cpp_gc_disable_t il2cpp_gc_disable = NULL;
il2cpp_gc_enable_t il2cpp_gc_enable = NULL;
il2cpp_gc_is_disabled_t il2cpp_gc_is_disabled = NULL;
il2cpp_gc_get_used_size_t il2cpp_gc_get_used_size = NULL;
il2cpp_gc_get_heap_size_t il2cpp_gc_get_heap_size = NULL;
il2cpp_gc_wbarrier_set_field_t il2cpp_gc_wbarrier_set_field = NULL;

il2cpp_gchandle_new_t il2cpp_gchandle_new = NULL;
il2cpp_gchandle_new_weakref_t il2cpp_gchandle_new_weakref = NULL;
il2cpp_gchandle_get_target_t il2cpp_gchandle_get_target = NULL;
il2cpp_gchandle_free_t il2cpp_gchandle_free = NULL;

il2cpp_method_get_return_type_t il2cpp_method_get_return_type = NULL;
il2cpp_method_get_declaring_type_t il2cpp_method_get_declaring_type = NULL;
il2cpp_method_get_name_t il2cpp_method_get_name = NULL;
il2cpp_method_get_from_reflection_t il2cpp_method_get_from_reflection = NULL;
il2cpp_method_get_object_t il2cpp_method_get_object = NULL;
il2cpp_method_is_generic_t il2cpp_method_is_generic = NULL;
il2cpp_method_is_inflated_t il2cpp_method_is_inflated = NULL;
il2cpp_method_is_instance_t il2cpp_method_is_instance = NULL;
il2cpp_method_get_param_count_t il2cpp_method_get_param_count = NULL;
il2cpp_method_get_param_t il2cpp_method_get_param = NULL;
il2cpp_method_get_class_t il2cpp_method_get_class = NULL;
il2cpp_method_has_attribute_t il2cpp_method_has_attribute = NULL;
il2cpp_method_get_flags_t il2cpp_method_get_flags = NULL;
il2cpp_method_get_token_t il2cpp_method_get_token = NULL;
il2cpp_method_get_param_name_t il2cpp_method_get_param_name = NULL;

il2cpp_property_get_flags_t il2cpp_property_get_flags = NULL;
il2cpp_property_get_get_method_t il2cpp_property_get_get_method = NULL;
il2cpp_property_get_set_method_t il2cpp_property_get_set_method = NULL;
il2cpp_property_get_name_t il2cpp_property_get_name = NULL;
il2cpp_property_get_parent_t il2cpp_property_get_parent = NULL;

il2cpp_object_get_class_t il2cpp_object_get_class = NULL;
il2cpp_object_get_size_t il2cpp_object_get_size = NULL;
il2cpp_object_get_virtual_method_t il2cpp_object_get_virtual_method = NULL;
il2cpp_object_new_t il2cpp_object_new = NULL;
il2cpp_object_unbox_t il2cpp_object_unbox = NULL;
il2cpp_value_box_t il2cpp_value_box = NULL;

il2cpp_monitor_enter_t il2cpp_monitor_enter = NULL;
il2cpp_monitor_try_enter_t il2cpp_monitor_try_enter = NULL;
il2cpp_monitor_exit_t il2cpp_monitor_exit = NULL;
il2cpp_monitor_pulse_t il2cpp_monitor_pulse = NULL;
il2cpp_monitor_pulse_all_t il2cpp_monitor_pulse_all = NULL;
il2cpp_monitor_wait_t il2cpp_monitor_wait = NULL;
il2cpp_monitor_try_wait_t il2cpp_monitor_try_wait = NULL;

il2cpp_runtime_invoke_t il2cpp_runtime_invoke = NULL;
il2cpp_runtime_invoke_convert_args_t il2cpp_runtime_invoke_convert_args = NULL;
il2cpp_runtime_class_init_t il2cpp_runtime_class_init = NULL;
il2cpp_runtime_object_init_t il2cpp_runtime_object_init = NULL;
il2cpp_runtime_object_init_exception_t il2cpp_runtime_object_init_exception = NULL;
il2cpp_runtime_unhandled_exception_policy_set_t il2cpp_runtime_unhandled_exception_policy_set = NULL;

il2cpp_string_length_t il2cpp_string_length = NULL;
il2cpp_string_chars_t il2cpp_string_chars = NULL;
il2cpp_string_new_t il2cpp_string_new = NULL;
il2cpp_string_new_len_t il2cpp_string_new_len = NULL;
il2cpp_string_new_utf16_t il2cpp_string_new_utf16 = NULL;
il2cpp_string_new_wrapper_t il2cpp_string_new_wrapper = NULL;
il2cpp_string_intern_t il2cpp_string_intern = NULL;
il2cpp_string_is_interned_t il2cpp_string_is_interned = NULL;

il2cpp_thread_current_t il2cpp_thread_current = NULL;
il2cpp_thread_attach_t il2cpp_thread_attach = NULL;
il2cpp_thread_detach_t il2cpp_thread_detach = NULL;
il2cpp_thread_get_all_attached_threads_t il2cpp_thread_get_all_attached_threads = NULL;
il2cpp_is_vm_thread_t il2cpp_is_vm_thread = NULL;

il2cpp_type_get_object_t il2cpp_type_get_object = NULL;
il2cpp_type_get_type_t il2cpp_type_get_type = NULL;
il2cpp_type_get_class_or_element_class_t il2cpp_type_get_class_or_element_class = NULL;
il2cpp_type_get_name_t il2cpp_type_get_name = NULL;
il2cpp_type_is_byref_t il2cpp_type_is_byref = NULL;
il2cpp_type_get_attrs_t il2cpp_type_get_attrs = NULL;
il2cpp_type_equals_t il2cpp_type_equals = NULL;
il2cpp_type_get_assembly_qualified_name_t il2cpp_type_get_assembly_qualified_name = NULL;

il2cpp_image_get_assembly_t il2cpp_image_get_assembly = NULL;
il2cpp_image_get_name_t il2cpp_image_get_name = NULL;
il2cpp_image_get_filename_t il2cpp_image_get_filename = NULL;
il2cpp_image_get_entry_point_t il2cpp_image_get_entry_point = NULL;
il2cpp_image_get_class_count_t il2cpp_image_get_class_count = NULL;
il2cpp_image_get_class_t il2cpp_image_get_class = NULL;

il2cpp_capture_memory_snapshot_t il2cpp_capture_memory_snapshot = NULL;
il2cpp_free_captured_memory_snapshot_t il2cpp_free_captured_memory_snapshot = NULL;

il2cpp_set_find_plugin_callback_t il2cpp_set_find_plugin_callback = NULL;

il2cpp_register_log_callback_t il2cpp_register_log_callback = NULL;

il2cpp_debugger_set_agent_options_t il2cpp_debugger_set_agent_options = NULL;
il2cpp_is_debugger_attached_t il2cpp_is_debugger_attached = NULL;

il2cpp_unity_install_unitytls_interface_t il2cpp_unity_install_unitytls_interface = NULL;
il2cpp_custom_attrs_from_class_t il2cpp_custom_attrs_from_class = NULL;
il2cpp_custom_attrs_from_method_t il2cpp_custom_attrs_from_method = NULL;
il2cpp_custom_attrs_get_attr_t il2cpp_custom_attrs_get_attr = NULL;
il2cpp_custom_attrs_has_attr_t il2cpp_custom_attrs_has_attr = NULL;
il2cpp_custom_attrs_construct_t il2cpp_custom_attrs_construct = NULL;
il2cpp_custom_attrs_free_t il2cpp_custom_attrs_free = NULL;
#pragma endregion
#pragma region Custom Functions
void* il2cpp_array_get(IL2CPPArray* _array, size_t size, int index) {
	return (void*)il2cpp_array_addr_with_size(_array, size, index);
}
void il2cpp_array_set(IL2CPPArray* _array, size_t size, int index, char* obj) {
	*il2cpp_array_addr_with_size(_array, size, index) = *obj;
}
#pragma endregion

void Build_IL2CPP(HMODULE hMono) {
	if (!hMono)
		return;

	// Grab Mono functions
	il2cpp_init = (il2cpp_init_t)GetProcAddress(hMono, "il2cpp_init");
	il2cpp_init_utf16 = (il2cpp_init_utf16_t)GetProcAddress(hMono, "il2cpp_init_utf16");
	il2cpp_shutdown = (il2cpp_shutdown_t)GetProcAddress(hMono, "il2cpp_shutdown");
	il2cpp_set_config_dir = (il2cpp_set_config_dir_t)GetProcAddress(hMono, "il2cpp_set_config_dir");
	il2cpp_set_data_dir = (il2cpp_set_data_dir_t)GetProcAddress(hMono, "il2cpp_set_data_dir");
	il2cpp_set_temp_dir = (il2cpp_set_temp_dir_t)GetProcAddress(hMono, "il2cpp_set_temp_dir");
	il2cpp_set_commandline_arguments = (il2cpp_set_commandline_arguments_t)GetProcAddress(hMono, "il2cpp_set_commandline_arguments");
	il2cpp_set_commandline_arguments_utf16 = (il2cpp_set_commandline_arguments_utf16_t)GetProcAddress(hMono, "il2cpp_set_commandline_arguments_utf16");
	il2cpp_set_config_utf16 = (il2cpp_set_config_utf16_t)GetProcAddress(hMono, "il2cpp_set_config_utf16");
	il2cpp_set_config = (il2cpp_set_config_t)GetProcAddress(hMono, "il2cpp_set_config");

	il2cpp_get_corlib = (il2cpp_get_corlib_t)GetProcAddress(hMono, "il2cpp_get_corlib");
	il2cpp_add_internal_call = (il2cpp_add_internal_call_t)GetProcAddress(hMono, "il2cpp_add_internal_call");
	il2cpp_resolve_icall = (il2cpp_resolve_icall_t)GetProcAddress(hMono, "il2cpp_resolve_icall");

	il2cpp_alloc = (il2cpp_alloc_t)GetProcAddress(hMono, "il2cpp_alloc");
	il2cpp_free = (il2cpp_free_t)GetProcAddress(hMono, "il2cpp_free");

	il2cpp_array_class_get = (il2cpp_array_class_get_t)GetProcAddress(hMono, "il2cpp_array_class_get");
	il2cpp_array_length = (il2cpp_array_length_t)GetProcAddress(hMono, "il2cpp_array_length");
	il2cpp_array_get_byte_length = (il2cpp_array_get_byte_length_t)GetProcAddress(hMono, "il2cpp_array_get_byte_length");
	il2cpp_array_new = (il2cpp_array_new_t)GetProcAddress(hMono, "il2cpp_array_new");
	il2cpp_array_new_specific = (il2cpp_array_new_specific_t)GetProcAddress(hMono, "il2cpp_array_new_specific");
	il2cpp_array_new_full = (il2cpp_array_new_full_t)GetProcAddress(hMono, "il2cpp_array_new_full");
	il2cpp_bounded_array_class_get = (il2cpp_bounded_array_class_get_t)GetProcAddress(hMono, "il2cpp_bounded_array_class_get");
	il2cpp_array_element_size = (il2cpp_array_element_size_t)GetProcAddress(hMono, "il2cpp_array_element_size");

	il2cpp_class_enum_basetype = (il2cpp_class_enum_basetype_t)GetProcAddress(hMono, "il2cpp_class_enum_basetype");
	il2cpp_class_is_generic = (il2cpp_class_is_generic_t)GetProcAddress(hMono, "il2cpp_class_is_generic");
	il2cpp_class_is_inflated = (il2cpp_class_is_inflated_t)GetProcAddress(hMono, "il2cpp_class_is_inflated");
	il2cpp_class_is_assignable_from = (il2cpp_class_is_assignable_from_t)GetProcAddress(hMono, "il2cpp_class_is_assignable_from");
	il2cpp_class_is_subclass_of = (il2cpp_class_is_subclass_of_t)GetProcAddress(hMono, "il2cpp_class_is_subclass_of");
	il2cpp_class_has_parent = (il2cpp_class_has_parent_t)GetProcAddress(hMono, "il2cpp_class_has_parent");
	il2cpp_class_from_il2cpp_type = (il2cpp_class_from_il2cpp_type_t)GetProcAddress(hMono, "il2cpp_class_from_il2cpp_type");
	il2cpp_class_from_name = (il2cpp_class_from_name_t)GetProcAddress(hMono, "il2cpp_class_from_name");
	il2cpp_class_from_system_type = (il2cpp_class_from_system_type_t)GetProcAddress(hMono, "il2cpp_class_from_system_type");
	il2cpp_class_get_element_class = (il2cpp_class_get_element_class_t)GetProcAddress(hMono, "il2cpp_class_get_element_class");
	il2cpp_class_get_events = (il2cpp_class_get_events_t)GetProcAddress(hMono, "il2cpp_class_get_events");
	il2cpp_class_get_fields = (il2cpp_class_get_fields_t)GetProcAddress(hMono, "il2cpp_class_get_fields");
	il2cpp_class_get_nested_types = (il2cpp_class_get_nested_types_t)GetProcAddress(hMono, "il2cpp_class_get_nested_types");
	il2cpp_class_get_interfaces = (il2cpp_class_get_interfaces_t)GetProcAddress(hMono, "il2cpp_class_get_interfaces");
	il2cpp_class_get_properties = (il2cpp_class_get_properties_t)GetProcAddress(hMono, "il2cpp_class_get_properties");
	il2cpp_class_get_property_from_name = (il2cpp_class_get_property_from_name_t)GetProcAddress(hMono, "il2cpp_class_get_property_from_name");
	il2cpp_class_get_field_from_name = (il2cpp_class_get_field_from_name_t)GetProcAddress(hMono, "il2cpp_class_get_field_from_name");
	il2cpp_class_get_methods = (il2cpp_class_get_methods_t)GetProcAddress(hMono, "il2cpp_class_get_methods");
	il2cpp_class_get_method_from_name = (il2cpp_class_get_method_from_name_t)GetProcAddress(hMono, "il2cpp_class_get_method_from_name");
	il2cpp_class_get_name = (il2cpp_class_get_name_t)GetProcAddress(hMono, "il2cpp_class_get_name");
	il2cpp_class_get_namespace = (il2cpp_class_get_namespace_t)GetProcAddress(hMono, "il2cpp_class_get_namespace");
	il2cpp_class_get_parent = (il2cpp_class_get_parent_t)GetProcAddress(hMono, "il2cpp_class_get_parent");
	il2cpp_class_get_declaring_type = (il2cpp_class_get_declaring_type_t)GetProcAddress(hMono, "il2cpp_class_get_declaring_type");
	il2cpp_class_instance_size = (il2cpp_class_instance_size_t)GetProcAddress(hMono, "il2cpp_class_instance_size");
	il2cpp_class_num_fields = (il2cpp_class_num_fields_t)GetProcAddress(hMono, "il2cpp_class_num_fields");
	il2cpp_class_is_valuetype = (il2cpp_class_is_valuetype_t)GetProcAddress(hMono, "il2cpp_class_is_valuetype");
	il2cpp_class_value_size = (il2cpp_class_value_size_t)GetProcAddress(hMono, "il2cpp_class_value_size");
	il2cpp_class_is_blittable = (il2cpp_class_is_blittable_t)GetProcAddress(hMono, "il2cpp_class_is_blittable");
	il2cpp_class_get_flags = (il2cpp_class_get_flags_t)GetProcAddress(hMono, "il2cpp_class_get_flags");
	il2cpp_class_is_abstract = (il2cpp_class_is_abstract_t)GetProcAddress(hMono, "il2cpp_class_is_abstract");
	il2cpp_class_is_interface = (il2cpp_class_is_interface_t)GetProcAddress(hMono, "il2cpp_class_is_interface");
	il2cpp_class_array_element_size = (il2cpp_class_array_element_size_t)GetProcAddress(hMono, "il2cpp_class_array_element_size");
	il2cpp_class_from_type = (il2cpp_class_from_type_t)GetProcAddress(hMono, "il2cpp_class_from_type");
	il2cpp_class_get_type = (il2cpp_class_get_type_t)GetProcAddress(hMono, "il2cpp_class_get_type");
	il2cpp_class_get_type_token = (il2cpp_class_get_type_token_t)GetProcAddress(hMono, "il2cpp_class_get_type_token");
	il2cpp_class_has_attribute = (il2cpp_class_has_attribute_t)GetProcAddress(hMono, "il2cpp_class_has_attribute");
	il2cpp_class_has_references = (il2cpp_class_has_references_t)GetProcAddress(hMono, "il2cpp_class_has_references");
	il2cpp_class_is_enum = (il2cpp_class_is_enum_t)GetProcAddress(hMono, "il2cpp_class_is_enum");
	il2cpp_class_get_image = (il2cpp_class_get_image_t)GetProcAddress(hMono, "il2cpp_class_get_image");
	il2cpp_class_get_assemblyname = (il2cpp_class_get_assemblyname_t)GetProcAddress(hMono, "il2cpp_class_get_assemblyname");
	il2cpp_class_get_rank = (il2cpp_class_get_rank_t)GetProcAddress(hMono, "il2cpp_class_get_rank");
	il2cpp_class_get_bitmap_size = (il2cpp_class_get_bitmap_size_t)GetProcAddress(hMono, "il2cpp_class_get_bitmap_size");
	il2cpp_class_get_bitmap = (il2cpp_class_get_bitmap_t)GetProcAddress(hMono, "il2cpp_class_get_bitmap");

	il2cpp_domain_get = (il2cpp_domain_get_t)GetProcAddress(hMono, "il2cpp_domain_get");
	il2cpp_domain_assembly_open = (il2cpp_domain_assembly_open_t)GetProcAddress(hMono, "il2cpp_domain_assembly_open");
	il2cpp_domain_get_assemblies = (il2cpp_domain_get_assemblies_t)GetProcAddress(hMono, "il2cpp_domain_get_assemblies");
	il2cpp_assembly_get_image = (il2cpp_assembly_get_image_t)GetProcAddress(hMono, "il2cpp_assembly_get_image");

	il2cpp_raise_exception = (il2cpp_raise_exception_t)GetProcAddress(hMono, "il2cpp_raise_exception");
	il2cpp_exception_from_name_msg = (il2cpp_exception_from_name_msg_t)GetProcAddress(hMono, "il2cpp_exception_from_name_msg");
	il2cpp_get_exception_argument_null = (il2cpp_get_exception_argument_null_t)GetProcAddress(hMono, "il2cpp_get_exception_argument_null");
	il2cpp_format_exception = (il2cpp_format_exception_t)GetProcAddress(hMono, "il2cpp_format_exception");
	il2cpp_format_stack_trace = (il2cpp_format_stack_trace_t)GetProcAddress(hMono, "il2cpp_format_stack_trace");
	il2cpp_unhandled_exception = (il2cpp_unhandled_exception_t)GetProcAddress(hMono, "il2cpp_unhandled_exception");

	il2cpp_field_get_flags = (il2cpp_field_get_flags_t)GetProcAddress(hMono, "il2cpp_field_get_flags");
	il2cpp_field_get_name = (il2cpp_field_get_name_t)GetProcAddress(hMono, "il2cpp_field_get_name");
	il2cpp_field_get_parent = (il2cpp_field_get_parent_t)GetProcAddress(hMono, "il2cpp_field_get_parent");
	il2cpp_field_get_offset = (il2cpp_field_get_offset_t)GetProcAddress(hMono, "il2cpp_field_get_offset");
	il2cpp_field_get_type = (il2cpp_field_get_type_t)GetProcAddress(hMono, "il2cpp_field_get_type");
	il2cpp_field_get_value = (il2cpp_field_get_value_t)GetProcAddress(hMono, "il2cpp_field_get_value");
	il2cpp_field_get_value_object = (il2cpp_field_get_value_object_t)GetProcAddress(hMono, "il2cpp_field_get_value_object");
	il2cpp_field_has_attribute = (il2cpp_field_has_attribute_t)GetProcAddress(hMono, "il2cpp_field_has_attribute");
	il2cpp_field_set_value = (il2cpp_field_set_value_t)GetProcAddress(hMono, "il2cpp_field_set_value");
	il2cpp_field_static_get_value = (il2cpp_field_static_get_value_t)GetProcAddress(hMono, "il2cpp_field_static_get_value");
	il2cpp_field_static_set_value = (il2cpp_field_static_set_value_t)GetProcAddress(hMono, "il2cpp_field_static_set_value");
	il2cpp_field_set_value_object = (il2cpp_field_set_value_object_t)GetProcAddress(hMono, "il2cpp_field_set_value_object");

	il2cpp_gc_collect = (il2cpp_gc_collect_t)GetProcAddress(hMono, "il2cpp_gc_collect");
	il2cpp_gc_collect_a_little = (il2cpp_gc_collect_a_little_t)GetProcAddress(hMono, "il2cpp_gc_collect_a_little");
	il2cpp_gc_disable = (il2cpp_gc_disable_t)GetProcAddress(hMono, "il2cpp_gc_disable");
	il2cpp_gc_enable = (il2cpp_gc_enable_t)GetProcAddress(hMono, "il2cpp_gc_enable");
	il2cpp_gc_is_disabled = (il2cpp_gc_is_disabled_t)GetProcAddress(hMono, "il2cpp_gc_is_disabled");
	il2cpp_gc_get_used_size = (il2cpp_gc_get_used_size_t)GetProcAddress(hMono, "il2cpp_gc_get_used_size");
	il2cpp_gc_get_heap_size = (il2cpp_gc_get_heap_size_t)GetProcAddress(hMono, "il2cpp_gc_get_heap_size");
	il2cpp_gc_wbarrier_set_field = (il2cpp_gc_wbarrier_set_field_t)GetProcAddress(hMono, "il2cpp_gc_wbarrier_set_field");

	il2cpp_gchandle_new = (il2cpp_gchandle_new_t)GetProcAddress(hMono, "il2cpp_gchandle_new");
	il2cpp_gchandle_new_weakref = (il2cpp_gchandle_new_weakref_t)GetProcAddress(hMono, "il2cpp_gchandle_new_weakref");
	il2cpp_gchandle_get_target = (il2cpp_gchandle_get_target_t)GetProcAddress(hMono, "il2cpp_gchandle_get_target");
	il2cpp_gchandle_free = (il2cpp_gchandle_free_t)GetProcAddress(hMono, "il2cpp_gchandle_free");

	il2cpp_method_get_return_type = (il2cpp_method_get_return_type_t)GetProcAddress(hMono, "il2cpp_method_get_return_type");
	il2cpp_method_get_declaring_type = (il2cpp_method_get_declaring_type_t)GetProcAddress(hMono, "il2cpp_method_get_declaring_type");
	il2cpp_method_get_name = (il2cpp_method_get_name_t)GetProcAddress(hMono, "il2cpp_method_get_name");
	il2cpp_method_get_from_reflection = (il2cpp_method_get_from_reflection_t)GetProcAddress(hMono, "il2cpp_method_get_from_reflection");
	il2cpp_method_get_object = (il2cpp_method_get_object_t)GetProcAddress(hMono, "il2cpp_method_get_object");
	il2cpp_method_is_generic = (il2cpp_method_is_generic_t)GetProcAddress(hMono, "il2cpp_method_is_generic");
	il2cpp_method_is_inflated = (il2cpp_method_is_inflated_t)GetProcAddress(hMono, "il2cpp_method_is_inflated");
	il2cpp_method_is_instance = (il2cpp_method_is_instance_t)GetProcAddress(hMono, "il2cpp_method_is_instance");
	il2cpp_method_get_param_count = (il2cpp_method_get_param_count_t)GetProcAddress(hMono, "il2cpp_method_get_param_count");
	il2cpp_method_get_param = (il2cpp_method_get_param_t)GetProcAddress(hMono, "il2cpp_method_get_param");
	il2cpp_method_get_class = (il2cpp_method_get_class_t)GetProcAddress(hMono, "il2cpp_method_get_class");
	il2cpp_method_has_attribute = (il2cpp_method_has_attribute_t)GetProcAddress(hMono, "il2cpp_method_has_attribute");
	il2cpp_method_get_flags = (il2cpp_method_get_flags_t)GetProcAddress(hMono, "il2cpp_method_get_flags");
	il2cpp_method_get_token = (il2cpp_method_get_token_t)GetProcAddress(hMono, "il2cpp_method_get_token");
	il2cpp_method_get_param_name = (il2cpp_method_get_param_name_t)GetProcAddress(hMono, "il2cpp_method_get_param_name");

	il2cpp_property_get_flags = (il2cpp_property_get_flags_t)GetProcAddress(hMono, "il2cpp_property_get_flags");
	il2cpp_property_get_get_method = (il2cpp_property_get_get_method_t)GetProcAddress(hMono, "il2cpp_property_get_get_method");
	il2cpp_property_get_set_method = (il2cpp_property_get_set_method_t)GetProcAddress(hMono, "il2cpp_property_get_set_method");
	il2cpp_property_get_name = (il2cpp_property_get_name_t)GetProcAddress(hMono, "il2cpp_property_get_name");
	il2cpp_property_get_parent = (il2cpp_property_get_parent_t)GetProcAddress(hMono, "il2cpp_property_get_parent");

	il2cpp_object_get_class = (il2cpp_object_get_class_t)GetProcAddress(hMono, "il2cpp_object_get_class");
	il2cpp_object_get_size = (il2cpp_object_get_size_t)GetProcAddress(hMono, "il2cpp_object_get_size");
	il2cpp_object_get_virtual_method = (il2cpp_object_get_virtual_method_t)GetProcAddress(hMono, "il2cpp_object_get_virtual_method");
	il2cpp_object_new = (il2cpp_object_new_t)GetProcAddress(hMono, "il2cpp_object_new");
	il2cpp_object_unbox = (il2cpp_object_unbox_t)GetProcAddress(hMono, "il2cpp_object_unbox");
	il2cpp_value_box = (il2cpp_value_box_t)GetProcAddress(hMono, "il2cpp_value_box");

	il2cpp_monitor_enter = (il2cpp_monitor_enter_t)GetProcAddress(hMono, "il2cpp_monitor_enter");
	il2cpp_monitor_try_enter = (il2cpp_monitor_try_enter_t)GetProcAddress(hMono, "il2cpp_monitor_try_enter");
	il2cpp_monitor_exit = (il2cpp_monitor_exit_t)GetProcAddress(hMono, "il2cpp_monitor_exit");
	il2cpp_monitor_pulse = (il2cpp_monitor_pulse_t)GetProcAddress(hMono, "il2cpp_monitor_pulse");
	il2cpp_monitor_pulse_all = (il2cpp_monitor_pulse_all_t)GetProcAddress(hMono, "il2cpp_monitor_pulse_all");
	il2cpp_monitor_wait = (il2cpp_monitor_wait_t)GetProcAddress(hMono, "il2cpp_monitor_wait");
	il2cpp_monitor_try_wait = (il2cpp_monitor_try_wait_t)GetProcAddress(hMono, "il2cpp_monitor_try_wait");

	il2cpp_runtime_invoke = (il2cpp_runtime_invoke_t)GetProcAddress(hMono, "il2cpp_runtime_invoke");
	il2cpp_runtime_invoke_convert_args = (il2cpp_runtime_invoke_convert_args_t)GetProcAddress(hMono, "il2cpp_runtime_invoke_convert_args");
	il2cpp_runtime_class_init = (il2cpp_runtime_class_init_t)GetProcAddress(hMono, "il2cpp_runtime_class_init");
	il2cpp_runtime_object_init = (il2cpp_runtime_object_init_t)GetProcAddress(hMono, "il2cpp_runtime_object_init");
	il2cpp_runtime_object_init_exception = (il2cpp_runtime_object_init_exception_t)GetProcAddress(hMono, "il2cpp_runtime_object_init_exception");
	il2cpp_runtime_unhandled_exception_policy_set = (il2cpp_runtime_unhandled_exception_policy_set_t)GetProcAddress(hMono, "il2cpp_runtime_unhandled_exception_policy_set");

	il2cpp_string_length = (il2cpp_string_length_t)GetProcAddress(hMono, "il2cpp_string_length");
	il2cpp_string_chars = (il2cpp_string_chars_t)GetProcAddress(hMono, "il2cpp_string_chars");
	il2cpp_string_new = (il2cpp_string_new_t)GetProcAddress(hMono, "il2cpp_string_new");
	il2cpp_string_new_len = (il2cpp_string_new_len_t)GetProcAddress(hMono, "il2cpp_string_new_len");
	il2cpp_string_new_utf16 = (il2cpp_string_new_utf16_t)GetProcAddress(hMono, "il2cpp_string_new_utf16");
	il2cpp_string_new_wrapper = (il2cpp_string_new_wrapper_t)GetProcAddress(hMono, "il2cpp_string_new_wrapper");
	il2cpp_string_intern = (il2cpp_string_intern_t)GetProcAddress(hMono, "il2cpp_string_intern");
	il2cpp_string_is_interned = (il2cpp_string_is_interned_t)GetProcAddress(hMono, "il2cpp_string_is_interned");

	il2cpp_thread_current = (il2cpp_thread_current_t)GetProcAddress(hMono, "il2cpp_thread_current");
	il2cpp_thread_attach = (il2cpp_thread_attach_t)GetProcAddress(hMono, "il2cpp_thread_attach");
	il2cpp_thread_detach = (il2cpp_thread_detach_t)GetProcAddress(hMono, "il2cpp_thread_detach");
	il2cpp_thread_get_all_attached_threads = (il2cpp_thread_get_all_attached_threads_t)GetProcAddress(hMono, "il2cpp_thread_get_all_attached_threads");
	il2cpp_is_vm_thread = (il2cpp_is_vm_thread_t)GetProcAddress(hMono, "il2cpp_is_vm_thread");

	il2cpp_type_get_object = (il2cpp_type_get_object_t)GetProcAddress(hMono, "il2cpp_type_get_object");
	il2cpp_type_get_type = (il2cpp_type_get_type_t)GetProcAddress(hMono, "il2cpp_type_get_type");
	il2cpp_type_get_class_or_element_class = (il2cpp_type_get_class_or_element_class_t)GetProcAddress(hMono, "il2cpp_type_get_class_or_element_class");
	il2cpp_type_get_name = (il2cpp_type_get_name_t)GetProcAddress(hMono, "il2cpp_type_get_name");
	il2cpp_type_is_byref = (il2cpp_type_is_byref_t)GetProcAddress(hMono, "il2cpp_type_is_byref");
	il2cpp_type_get_attrs = (il2cpp_type_get_attrs_t)GetProcAddress(hMono, "il2cpp_type_get_attrs");
	il2cpp_type_equals = (il2cpp_type_equals_t)GetProcAddress(hMono, "il2cpp_type_equals");
	il2cpp_type_get_assembly_qualified_name = (il2cpp_type_get_assembly_qualified_name_t)GetProcAddress(hMono, "il2cpp_type_get_assembly_qualified_name");

	il2cpp_image_get_assembly = (il2cpp_image_get_assembly_t)GetProcAddress(hMono, "il2cpp_image_get_assembly");
	il2cpp_image_get_name = (il2cpp_image_get_name_t)GetProcAddress(hMono, "il2cpp_image_get_name");
	il2cpp_image_get_filename = (il2cpp_image_get_filename_t)GetProcAddress(hMono, "il2cpp_image_get_filename");
	il2cpp_image_get_entry_point = (il2cpp_image_get_entry_point_t)GetProcAddress(hMono, "il2cpp_image_get_entry_point");
	il2cpp_image_get_class_count = (il2cpp_image_get_class_count_t)GetProcAddress(hMono, "il2cpp_image_get_class_count");
	il2cpp_image_get_class = (il2cpp_image_get_class_t)GetProcAddress(hMono, "il2cpp_image_get_class");

	il2cpp_capture_memory_snapshot = (il2cpp_capture_memory_snapshot_t)GetProcAddress(hMono, "il2cpp_capture_memory_snapshot");
	il2cpp_free_captured_memory_snapshot = (il2cpp_free_captured_memory_snapshot_t)GetProcAddress(hMono, "il2cpp_free_captured_memory_snapshot");

	il2cpp_set_find_plugin_callback = (il2cpp_set_find_plugin_callback_t)GetProcAddress(hMono, "il2cpp_set_find_plugin_callback");

	il2cpp_register_log_callback = (il2cpp_register_log_callback_t)GetProcAddress(hMono, "il2cpp_register_log_callback");

	il2cpp_debugger_set_agent_options = (il2cpp_debugger_set_agent_options_t)GetProcAddress(hMono, "il2cpp_debugger_set_agent_options");
	il2cpp_is_debugger_attached = (il2cpp_is_debugger_attached_t)GetProcAddress(hMono, "il2cpp_is_debugger_attached");

	il2cpp_unity_install_unitytls_interface = (il2cpp_unity_install_unitytls_interface_t)GetProcAddress(hMono, "il2cpp_unity_install_unitytls_interface");

	il2cpp_custom_attrs_from_class = (il2cpp_custom_attrs_from_class_t)GetProcAddress(hMono, "il2cpp_custom_attrs_from_class");
	il2cpp_custom_attrs_from_method = (il2cpp_custom_attrs_from_method_t)GetProcAddress(hMono, "il2cpp_custom_attrs_from_method");
	il2cpp_custom_attrs_get_attr = (il2cpp_custom_attrs_get_attr_t)GetProcAddress(hMono, "il2cpp_custom_attrs_get_attr");
	il2cpp_custom_attrs_has_attr = (il2cpp_custom_attrs_has_attr_t)GetProcAddress(hMono, "il2cpp_custom_attrs_has_attr");
	il2cpp_custom_attrs_construct = (il2cpp_custom_attrs_construct_t)GetProcAddress(hMono, "il2cpp_custom_attrs_construct");
	il2cpp_custom_attrs_free = (il2cpp_custom_attrs_free_t)GetProcAddress(hMono, "il2cpp_custom_attrs_free");

	// Log
	ConsoleUtils::Log("Built IL2CPP runtime!");
}