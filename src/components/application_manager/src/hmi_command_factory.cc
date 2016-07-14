/*
 Copyright (c) 2013, Ford Motor Company
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following
 disclaimer in the documentation and/or other materials provided with the
 distribution.

 Neither the name of the Ford Motor Company nor the names of its contributors
 may be used to endorse or promote products derived from this software
 without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

#include "application_manager/hmi_command_factory.h"

#include "application_manager/message.h"
#include "interfaces/HMI_API.h"

#include "application_manager/commands/hmi/update_device_list_request.h"
#include "application_manager/commands/hmi/update_device_list_response.h"
#include "application_manager/commands/hmi/on_update_device_list.h"
#include "application_manager/commands/hmi/on_start_device_discovery.h"
#include "application_manager/commands/hmi/update_app_list_request.h"
#include "application_manager/commands/hmi/update_app_list_response.h"
#include "application_manager/commands/hmi/on_find_applications.h"
#include "application_manager/commands/hmi/allow_all_apps_request.h"
#include "application_manager/commands/hmi/allow_all_apps_response.h"
#include "application_manager/commands/hmi/allow_app_request.h"
#include "application_manager/commands/hmi/allow_app_response.h"
#include "application_manager/commands/hmi/sdl_get_list_of_permissions_request.h"
#include "application_manager/commands/hmi/sdl_get_list_of_permissions_response.h"
#include "application_manager/commands/hmi/sdl_get_user_friendly_message_request.h"
#include "application_manager/commands/hmi/sdl_get_user_friendly_message_response.h"
#include "application_manager/commands/hmi/sdl_get_status_update_request.h"
#include "application_manager/commands/hmi/sdl_get_status_update_response.h"
#include "application_manager/commands/hmi/on_status_update_notification.h"
#include "application_manager/commands/hmi/update_sdl_request.h"
#include "application_manager/commands/hmi/update_sdl_response.h"
#include "application_manager/commands/hmi/activate_app_request.h"
#include "application_manager/commands/hmi/activate_app_response.h"
#include "application_manager/commands/hmi/mixing_audio_supported_request.h"
#include "application_manager/commands/hmi/mixing_audio_supported_response.h"
#include "application_manager/commands/hmi/on_allow_sdl_functionality_notification.h"
#include "application_manager/commands/hmi/on_app_permission_changed_notification.h"
#include "application_manager/commands/hmi/on_app_permission_consent_notification.h"
#include "application_manager/commands/hmi/on_app_activated_notification.h"
#include "application_manager/commands/hmi/on_audio_data_streaming_notification.h"
#include "application_manager/commands/hmi/on_video_data_streaming_notification.h"
#include "application_manager/commands/hmi/on_sdl_consent_needed_notification.h"
#include "application_manager/commands/hmi/on_exit_all_applications_notification.h"
#include "application_manager/commands/hmi/on_exit_application_notification.h"
#include "application_manager/commands/hmi/on_put_file_notification.h"
#include "application_manager/commands/hmi/on_resume_audio_source_notification.h"
#include "application_manager/commands/hmi/on_ignition_cycle_over_notification.h"
#include "application_manager/commands/hmi/on_system_info_changed_notification.h"
#include "application_manager/commands/hmi/get_system_info_request.h"
#include "application_manager/commands/hmi/get_system_info_response.h"
#include "application_manager/commands/hmi/close_popup_request.h"
#include "application_manager/commands/hmi/close_popup_response.h"
#include "application_manager/commands/hmi/button_get_capabilities_request.h"
#include "application_manager/commands/hmi/button_get_capabilities_response.h"
#include "application_manager/commands/hmi/ui_add_command_request.h"
#include "application_manager/commands/hmi/ui_add_command_response.h"
#include "application_manager/commands/hmi/ui_delete_command_request.h"
#include "application_manager/commands/hmi/ui_delete_command_response.h"
#include "application_manager/commands/hmi/ui_add_submenu_request.h"
#include "application_manager/commands/hmi/ui_add_submenu_response.h"
#include "application_manager/commands/hmi/ui_delete_submenu_request.h"
#include "application_manager/commands/hmi/ui_delete_submenu_response.h"
#include "application_manager/commands/hmi/ui_get_supported_languages_request.h"
#include "application_manager/commands/hmi/ui_get_supported_languages_response.h"
#include "application_manager/commands/hmi/ui_get_language_request.h"
#include "application_manager/commands/hmi/ui_get_language_response.h"
#include "application_manager/commands/hmi/ui_get_capabilities_request.h"
#include "application_manager/commands/hmi/ui_get_capabilities_response.h"
#include "application_manager/commands/hmi/ui_change_registration_request.h"
#include "application_manager/commands/hmi/ui_change_registration_response.h"
#include "application_manager/commands/hmi/ui_show_request.h"
#include "application_manager/commands/hmi/ui_show_response.h"
#include "application_manager/commands/hmi/ui_alert_request.h"
#include "application_manager/commands/hmi/ui_alert_response.h"
#include "application_manager/commands/hmi/ui_is_ready_request.h"
#include "application_manager/commands/hmi/ui_is_ready_response.h"
#include "application_manager/commands/hmi/ui_slider_request.h"
#include "application_manager/commands/hmi/ui_slider_response.h"
#include "application_manager/commands/hmi/ui_set_media_clock_timer_request.h"
#include "application_manager/commands/hmi/ui_set_media_clock_timer_response.h"
#include "application_manager/commands/hmi/ui_set_global_properties_request.h"
#include "application_manager/commands/hmi/ui_set_global_properties_response.h"
#include "application_manager/commands/hmi/ui_scrollable_message_request.h"
#include "application_manager/commands/hmi/ui_scrollable_message_response.h"
#include "application_manager/commands/hmi/ui_set_app_icon_request.h"
#include "application_manager/commands/hmi/ui_set_app_icon_response.h"
#include "application_manager/commands/hmi/ui_perform_audio_pass_thru_response.h"
#include "application_manager/commands/hmi/ui_perform_audio_pass_thru_request.h"
#include "application_manager/commands/hmi/ui_end_audio_pass_thru_response.h"
#include "application_manager/commands/hmi/ui_end_audio_pass_thru_request.h"
#include "application_manager/commands/hmi/ui_perform_interaction_request.h"
#include "application_manager/commands/hmi/ui_perform_interaction_response.h"
#include "application_manager/commands/hmi/vr_is_ready_request.h"
#include "application_manager/commands/hmi/vr_is_ready_response.h"
#include "application_manager/commands/hmi/vr_add_command_request.h"
#include "application_manager/commands/hmi/vr_add_command_response.h"
#include "application_manager/commands/hmi/vr_delete_command_request.h"
#include "application_manager/commands/hmi/vr_delete_command_response.h"
#include "application_manager/commands/hmi/vr_change_registration_request.h"
#include "application_manager/commands/hmi/vr_change_registration_response.h"
#include "application_manager/commands/hmi/vr_get_supported_languages_request.h"
#include "application_manager/commands/hmi/vr_get_supported_languages_response.h"
#include "application_manager/commands/hmi/vr_get_language_request.h"
#include "application_manager/commands/hmi/vr_get_language_response.h"
#include "application_manager/commands/hmi/vr_get_capabilities_request.h"
#include "application_manager/commands/hmi/vr_get_capabilities_response.h"
#include "application_manager/commands/hmi/tts_is_ready_request.h"
#include "application_manager/commands/hmi/tts_is_ready_response.h"
#include "application_manager/commands/hmi/tts_change_registration_request.h"
#include "application_manager/commands/hmi/tts_change_registration_response.h"
#include "application_manager/commands/hmi/tts_get_supported_languages_request.h"
#include "application_manager/commands/hmi/tts_get_supported_languages_response.h"
#include "application_manager/commands/hmi/tts_get_language_request.h"
#include "application_manager/commands/hmi/tts_get_language_response.h"
#include "application_manager/commands/hmi/tts_stop_speaking_request.h"
#include "application_manager/commands/hmi/tts_stop_speaking_response.h"
#include "application_manager/commands/hmi/tts_speak_request.h"
#include "application_manager/commands/hmi/tts_speak_response.h"
#include "application_manager/commands/hmi/tts_set_global_properties_request.h"
#include "application_manager/commands/hmi/tts_set_global_properties_response.h"
#include "application_manager/commands/hmi/tts_get_capabilities_request.h"
#include "application_manager/commands/hmi/tts_get_capabilities_response.h"
#include "application_manager/commands/hmi/vr_perform_interaction_request.h"
#include "application_manager/commands/hmi/vr_perform_interaction_response.h"
#include "application_manager/commands/hmi/vi_is_ready_request.h"
#include "application_manager/commands/hmi/vi_is_ready_response.h"
#include "application_manager/commands/hmi/vi_read_did_request.h"
#include "application_manager/commands/hmi/vi_read_did_response.h"
#include "application_manager/commands/hmi/sdl_activate_app_request.h"
#include "application_manager/commands/hmi/sdl_activate_app_response.h"
#include "application_manager/commands/hmi/on_app_permission_changed_notification.h"
#include "application_manager/commands/hmi/on_event_changed_notification.h"

#ifdef HMI_DBUS_API
#include "application_manager/commands/hmi/vi_get_vehicle_data_request_template.h"
#include "application_manager/commands/hmi/vi_get_vehicle_data_response_template.h"
#include "application_manager/commands/hmi/vi_subscribe_vehicle_data_request_template.h"
#include "application_manager/commands/hmi/vi_subscribe_vehicle_data_response_template.h"
#include "application_manager/commands/hmi/vi_unsubscribe_vehicle_data_request_template.h"
#include "application_manager/commands/hmi/vi_unsubscribe_vehicle_data_response_template.h"
#include "application_manager/commands/hmi/on_vi_gps_data_notification.h"
#include "application_manager/commands/hmi/on_vi_speed_notification.h"
#include "application_manager/commands/hmi/on_vi_rpm_notification.h"
#include "application_manager/commands/hmi/on_vi_fuel_level_notification.h"
#include "application_manager/commands/hmi/on_vi_fuel_level_state_notification.h"
#include "application_manager/commands/hmi/on_vi_instant_fuel_consumption_notification.h"
#include "application_manager/commands/hmi/on_vi_external_temperature_notification.h"
#include "application_manager/commands/hmi/on_vi_vin_notification.h"
#include "application_manager/commands/hmi/on_vi_prndl_notification.h"
#include "application_manager/commands/hmi/on_vi_tire_pressure_notification.h"
#include "application_manager/commands/hmi/on_vi_odometer_notification.h"
#include "application_manager/commands/hmi/on_vi_belt_status_notification.h"
#include "application_manager/commands/hmi/on_vi_body_information_notification.h"
#include "application_manager/commands/hmi/on_vi_device_status_notification.h"
#include "application_manager/commands/hmi/on_vi_driver_braking_notification.h"
#include "application_manager/commands/hmi/on_vi_wiper_status_notification.h"
#include "application_manager/commands/hmi/on_vi_head_lamp_status_notification.h"
#include "application_manager/commands/hmi/on_vi_engine_torque_notification.h"
#include "application_manager/commands/hmi/on_vi_acc_pedal_position_notification.h"
#include "application_manager/commands/hmi/on_vi_steering_wheel_angle_notification.h"
#include "application_manager/commands/hmi/on_vi_my_key_notification.h"
#else
#include "application_manager/commands/hmi/vi_get_vehicle_data_request.h"
#include "application_manager/commands/hmi/vi_get_vehicle_data_response.h"
#include "application_manager/commands/hmi/on_vi_vehicle_data_notification.h"
#include "application_manager/commands/hmi/vi_subscribe_vehicle_data_request.h"
#include "application_manager/commands/hmi/vi_subscribe_vehicle_data_response.h"
#include "application_manager/commands/hmi/vi_unsubscribe_vehicle_data_request.h"
#include "application_manager/commands/hmi/vi_unsubscribe_vehicle_data_response.h"
#endif  // #ifdef HMI_DBUS_API

#include "application_manager/commands/hmi/vi_get_dtcs_request.h"
#include "application_manager/commands/hmi/vi_get_dtcs_response.h"
#include "application_manager/commands/hmi/vi_diagnostic_message_request.h"
#include "application_manager/commands/hmi/vi_diagnostic_message_response.h"
#include "application_manager/commands/hmi/vi_get_vehicle_type_request.h"
#include "application_manager/commands/hmi/vi_get_vehicle_type_response.h"
#include "application_manager/commands/hmi/navi_is_ready_request.h"
#include "application_manager/commands/hmi/navi_show_constant_tbt_request.h"
#include "application_manager/commands/hmi/navi_show_constant_tbt_response.h"
#include "application_manager/commands/hmi/navi_is_ready_response.h"
#include "application_manager/commands/hmi/navi_alert_maneuver_request.h"
#include "application_manager/commands/hmi/navi_alert_maneuver_response.h"
#include "application_manager/commands/hmi/navi_update_turn_list_request.h"
#include "application_manager/commands/hmi/navi_update_turn_list_response.h"
#include "application_manager/commands/hmi/navi_subscribe_way_points_request.h"
#include "application_manager/commands/hmi/navi_subscribe_way_points_response.h"
#include "application_manager/commands/hmi/navi_unsubscribe_way_points_request.h"
#include "application_manager/commands/hmi/navi_unsubscribe_way_points_response.h"
#include "application_manager/commands/hmi/navi_get_way_points_request.h"
#include "application_manager/commands/hmi/navi_get_way_points_response.h"
#include "application_manager/commands/hmi/on_ready_notification.h"
#include "application_manager/commands/hmi/on_device_chosen_notification.h"
#include "application_manager/commands/hmi/on_file_removed_notification.h"
#include "application_manager/commands/hmi/on_system_context_notification.h"
#include "application_manager/commands/hmi/on_app_registered_notification.h"
#include "application_manager/commands/hmi/on_app_unregistered_notification.h"
#include "application_manager/commands/hmi/on_driver_distraction_notification.h"
#include "application_manager/commands/hmi/on_tts_started_notification.h"
#include "application_manager/commands/hmi/on_tts_stopped_notification.h"
#include "application_manager/commands/hmi/on_vr_started_notification.h"
#include "application_manager/commands/hmi/on_vr_stopped_notification.h"
#include "application_manager/commands/hmi/on_vr_command_notification.h"
#include "application_manager/commands/hmi/on_ui_command_notification.h"
#include "application_manager/commands/hmi/on_app_deactivated_notification.h"
#include "application_manager/commands/hmi/on_ui_language_change_notification.h"
#include "application_manager/commands/hmi/on_vr_language_change_notification.h"
#include "application_manager/commands/hmi/on_tts_language_change_notification.h"
#include "application_manager/commands/hmi/on_navi_tbt_client_state_notification.h"
#include "application_manager/commands/hmi/on_navi_way_point_change_notification.h"
#include "application_manager/commands/hmi/on_button_event_notification.h"
#include "application_manager/commands/hmi/on_button_press_notification.h"
#include "application_manager/commands/hmi/on_button_subscription_notification.h"
#include "application_manager/commands/hmi/on_vi_vehicle_data_notification.h"
#include "application_manager/commands/hmi/on_ui_keyboard_input_notification.h"
#include "application_manager/commands/hmi/on_ui_touch_event_notification.h"
#include "application_manager/commands/hmi/on_ui_reset_timeout_notification.h"
#include "application_manager/commands/hmi/navi_start_stream_request.h"
#include "application_manager/commands/hmi/navi_start_stream_response.h"
#include "application_manager/commands/hmi/navi_stop_stream_request.h"
#include "application_manager/commands/hmi/navi_stop_stream_response.h"
#include "application_manager/commands/hmi/navi_audio_start_stream_request.h"
#include "application_manager/commands/hmi/navi_audio_start_stream_response.h"
#include "application_manager/commands/hmi/navi_audio_stop_stream_request.h"
#include "application_manager/commands/hmi/navi_audio_stop_stream_response.h"
#include "application_manager/commands/hmi/on_system_request_notification.h"
#include "application_manager/commands/hmi/ui_set_display_layout_request.h"
#include "application_manager/commands/hmi/ui_set_display_layout_response.h"
#include "application_manager/commands/hmi/on_sdl_close_notification.h"
#include "application_manager/commands/hmi/on_sdl_persistence_complete_notification.h"
#include "application_manager/commands/hmi/on_record_start_notification.h"
#include "application_manager/commands/hmi/add_statistics_info_notification.h"
#include "application_manager/commands/hmi/on_system_error_notification.h"
#include "application_manager/commands/hmi/basic_communication_system_request.h"
#include "application_manager/commands/hmi/basic_communication_system_response.h"
#include "application_manager/commands/hmi/sdl_policy_update.h"
#include "application_manager/commands/hmi/sdl_policy_update_response.h"
#include "application_manager/commands/hmi/on_received_policy_update.h"
#include "application_manager/commands/hmi/on_policy_update.h"
#include "application_manager/commands/hmi/get_urls.h"
#include "application_manager/commands/hmi/get_urls_response.h"
#include "application_manager/commands/hmi/on_device_state_changed_notification.h"
#include "application_manager/commands/hmi/navi_send_location_request.h"
#include "application_manager/commands/hmi/navi_send_location_response.h"
#include "application_manager/commands/hmi/on_tts_reset_timeout_notification.h"
#include "application_manager/commands/hmi/dial_number_request.h"
#include "application_manager/commands/hmi/dial_number_response.h"

CREATE_LOGGERPTR_GLOBAL(logger_, "ApplicationManager")
namespace application_manager {

CommandSharedPtr HMICommandFactory::CreateCommand(
    const commands::MessageSharedPtr& message,
    ApplicationManager& application_manager) {
  const int function_id =
      (*message)[strings::params][strings::function_id].asInt();
  LOG4CXX_DEBUG(
      logger_, "HMICommandFactory::CreateCommand function_id: " << function_id);

  CommandSharedPtr command(new(__FILE__, __LINE__) application_manager::commands::CommandImpl(
      message, application_manager));

  bool is_response = false;
  const int msg_type =
      (*message)[strings::params][strings::message_type].asInt();
  if (msg_type ==
      static_cast<int>(application_manager::MessageType::kResponse)) {
    is_response = true;
    LOG4CXX_DEBUG(logger_, "HMICommandFactory::CreateCommand response");
  } else if ((*message)[strings::params][strings::message_type] ==
             static_cast<int>(
                 application_manager::MessageType::kErrorResponse)) {
    is_response = true;
    LOG4CXX_DEBUG(logger_, "HMICommandFactory::CreateCommand error response");
  } else {
    LOG4CXX_DEBUG(logger_, "HMICommandFactory::CreateCommand request");
  }

  switch (function_id) {
    case hmi_apis::FunctionID::BasicCommunication_OnStartDeviceDiscovery: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnStartDeviceDiscovery(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_UpdateDeviceList: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UpdateDeviceListResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::UpdateDeviceListRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_ActivateApp: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::ActivateAppResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::ActivateAppRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_GetSystemInfo: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::GetSystemInfoResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::GetSystemInfoRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::SDL_ActivateApp: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::SDLActivateAppResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::SDLActivateAppRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_PolicyUpdate: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::SDLPolicyUpdateResponse(
            message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::SDLPolicyUpdate(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::SDL_GetURLS: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::GetUrlsResponse(message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::GetUrls(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::SDL_OnAppPermissionChanged: {
      command.reset(new(__FILE__, __LINE__) commands::OnAppPermissionChangedNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::SDL_GetListOfPermissions: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::SDLGetListOfPermissionsResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::SDLGetListOfPermissionsRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::SDL_GetUserFriendlyMessage: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::SDLGetUserFriendlyMessageResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::SDLGetUserFriendlyMessageRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::SDL_GetStatusUpdate: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::SDLGetStatusUpdateResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::SDLGetStatusUpdateRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::SDL_OnStatusUpdate: {
      command.reset(new(__FILE__, __LINE__) commands::OnStatusUpdateNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::SDL_OnAppPermissionConsent: {
      command.reset(new(__FILE__, __LINE__) commands::OnAppPermissionConsentNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_MixingAudioSupported: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::MixingAudioSupportedResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::MixingAudioSupportedRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnExitAllApplications: {
      command.reset(new(__FILE__, __LINE__) commands::OnExitAllApplicationsNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::UI_AddCommand: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::UIAddCommandResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UIAddCommandRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_DeleteCommand: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UIDeleteCommandResponse(
            message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UIDeleteCommandRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_AddSubMenu: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::UIAddSubmenuResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UIAddSubmenuRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_DeleteSubMenu: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UIDeleteSubmenuResponse(
            message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UIDeleteSubmenuRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_SetMediaClockTimer: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UISetMediaClockTimerResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::UISetMediaClockTimerRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_PerformInteraction: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UIPerformInteractionResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::UIPerformInteractionRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_SetGlobalProperties: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UISetGlobalPropertiesResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::UISetGlobalPropertiesRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_ScrollableMessage: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UIScrollableMessageResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::UIScrollableMessageRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_SetAppIcon: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::UISetAppIconResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UISetAppIconRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_GetSupportedLanguages: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UIGetSupportedLanguagesResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::UIGetSupportedLanguagesRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_GetLanguage: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::UIGetLanguageResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UIGetLanguageRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_GetCapabilities: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UIGetCapabilitiesResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::UIGetCapabilitiesRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_ChangeRegistration: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UIChangeRegistratioResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::UIChangeRegistrationRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_PerformAudioPassThru: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UIPerformAudioPassThruResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::UIPerformAudioPassThruRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_EndAudioPassThru: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UIEndAudioPassThruResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::UIEndAudioPassThruRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_Alert: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::UIAlertResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UIAlertRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VR_IsReady: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::VRIsReadyResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::VRIsReadyRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VR_AddCommand: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::VRAddCommandResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::VRAddCommandRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VR_DeleteCommand: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::VRDeleteCommandResponse(
            message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::VRDeleteCommandRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VR_ChangeRegistration: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::VRChangeRegistrationResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::VRChangeRegistrationRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VR_GetSupportedLanguages: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::VRGetSupportedLanguagesResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::VRGetSupportedLanguagesRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VR_GetLanguage: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::VRGetLanguageResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::VRGetLanguageRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VR_GetCapabilities: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::VRGetCapabilitiesResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::VRGetCapabilitiesRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::TTS_IsReady: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::TTSIsReadyResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::TTSIsReadyRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::TTS_ChangeRegistration: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::TTSChangeRegistratioResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::TTSChangeRegistrationRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::TTS_GetSupportedLanguages: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::TTSGetSupportedLanguagesResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::TTSGetSupportedLanguagesRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::TTS_StopSpeaking: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::TTSStopSpeakingResponse(
            message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::TTSStopSpeakingRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::TTS_GetLanguage: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::TTSGetLanguageResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::TTSGetLanguageRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::TTS_Speak: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::TTSSpeakResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::TTSSpeakRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::TTS_SetGlobalProperties: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::TTSSetGlobalPropertiesResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::TTSSetGlobalPropertiesRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::TTS_GetCapabilities: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::TTSGetCapabilitiesResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::TTSGetCapabilitiesRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::TTS_Started: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnTTSStartedNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::TTS_Stopped: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnTTSStoppedNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnAppActivated: {
      command.reset(new(__FILE__, __LINE__) commands::OnAppActivatedNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnExitApplication: {
      command.reset(new(__FILE__, __LINE__) commands::OnExitApplicationNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::UI_Show: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::UIShowResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UIShowRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_Slider: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::UISliderResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UISliderRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_ClosePopUp: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::ClosePopupResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::ClosePopupRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::UI_IsReady: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::UIIsReadyResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UIIsReadyRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_IsReady: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::VIIsReadyResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::VIIsReadyRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_ReadDID: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::VIReadDIDResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::VIReadDIDRequest(message, application_manager));
      }
      break;
    }
#ifdef HMI_DBUS_API
    case hmi_apis::FunctionID::VehicleInfo_GetGpsData: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetGpsData>(message,
                                                          application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetGpsData>(message,
                                                          application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetSpeed: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetSpeed>(message,
                                                        application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetSpeed>(message,
                                                        application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetRpm: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetRpm>(message,
                                                      application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetRpm>(message,
                                                      application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetFuelLevel: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetFuelLevel>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetFuelLevel>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetFuelLevelState: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetFuelLevelState>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetFuelLevelState>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetInstantFuelConsumption: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetInstantFuelConsumption>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetInstantFuelConsumption>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetExternalTemperature: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetExternalTemperature>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetExternalTemperature>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetPrndl: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetPrndl>(message,
                                                        application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetPrndl>(message,
                                                        application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetVin: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetVin>(message,
                                                      application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetVin>(message,
                                                      application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetTirePressure: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetTirePressure>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetTirePressure>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetOdometer: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetOdometer>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetOdometer>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetBeltStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetBeltStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetBeltStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetBodyInformation: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetBodyInformation>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetBodyInformation>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetDeviceStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetDeviceStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetDeviceStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetDriverBraking: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetDriverBraking>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetDriverBraking>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetWiperStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetWiperStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetWiperStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetHeadLampStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetHeadLampStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetHeadLampStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetEngineTorque: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetEngineTorque>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetEngineTorque>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetAccPedalPosition: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetAccPedalPosition>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetAccPedalPosition>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetSteeringWheelAngle: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetSteeringWheelAngle>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetSteeringWheelAngle>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetECallInfo: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetECallInfo>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetECallInfo>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetAirbagStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetAirbagStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetAirbagStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetEmergencyEvent: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetEmergencyEvent>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetEmergencyEvent>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetClusterModeStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetClusterModeStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetClusterModeStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetMyKey: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetMyKey>(message,
                                                        application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_GetMyKey>(message,
                                                        application_manager));
      break;
    }
#else
    case hmi_apis::FunctionID::VehicleInfo_GetVehicleData: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleDataRequest(
            message, application_manager));
      }
      break;
    }
#endif  // #ifdef HMI_DBUS_API
    case hmi_apis::FunctionID::VehicleInfo_GetDTCs: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::VIGetDTCsResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::VIGetDTCsRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_DiagnosticMessage: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::VIDiagnosticMessageResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::VIDiagnosticMessageRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_GetVehicleType: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleTypeResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::VIGetVehicleTypeRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_IsReady: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::NaviIsReadyResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::NaviIsReadyRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_AlertManeuver: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::NaviAlertManeuverResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::NaviAlertManeuverRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_GetWayPoints: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::NaviGetWayPointsResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::NaviGetWayPointsRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_UpdateTurnList: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::NaviUpdateTurnListResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::NaviUpdateTurnListRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_ShowConstantTBT: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::NaviShowConstantTBTResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::NaviShowConstantTBTRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_SubscribeWayPoints: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::NaviSubscribeWayPointsResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::NaviSubscribeWayPointsRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_UnsubscribeWayPoints: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::NaviUnsubscribeWayPointsResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::NaviUnSubscribeWayPointsRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Buttons_GetCapabilities: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::ButtonGetCapabilitiesResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::ButtonGetCapabilitiesRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::SDL_OnAllowSDLFunctionality: {
      command.reset(new(__FILE__, __LINE__) commands::OnAllowSDLFunctionalityNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::SDL_OnSDLConsentNeeded: {
      command.reset(new(__FILE__, __LINE__) commands::OnSDLConsentNeededNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::SDL_UpdateSDL: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::UpdateSDLResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UpdateSDLRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnIgnitionCycleOver: {
      command.reset(new(__FILE__, __LINE__) commands::OnIgnitionCycleOverNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnSystemInfoChanged: {
      command.reset(new(__FILE__, __LINE__) commands::OnSystemInfoChangedNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnReady: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnReadyNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnDeviceChosen: {
      command.reset(new(__FILE__, __LINE__) commands::OnDeviceChosenNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::UI_OnSystemContext: {
      command.reset(new(__FILE__, __LINE__) commands::OnSystemContextNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::UI_OnDriverDistraction: {
      command.reset(new(__FILE__, __LINE__) commands::hmi::OnDriverDistractionNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnUpdateDeviceList: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnUpdateDeviceList(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnAppRegistered: {
      command.reset(new(__FILE__, __LINE__) commands::OnAppRegisteredNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnAppUnregistered: {
      command.reset(new(__FILE__, __LINE__) commands::OnAppUnregisteredNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnFindApplications: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnFindApplications(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_UpdateAppList: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::UpdateAppListResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::UpdateAppListRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::VR_Started: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnVRStartedNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VR_Stopped: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnVRStoppedNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VR_OnCommand: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnVRCommandNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::UI_OnCommand: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnUICommandNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnAppDeactivated: {
      command.reset(new(__FILE__, __LINE__) commands::OnAppDeactivatedNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::UI_OnLanguageChange: {
      command.reset(new(__FILE__, __LINE__) commands::OnUILanguageChangeNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VR_OnLanguageChange: {
      command.reset(new(__FILE__, __LINE__) commands::OnVRLanguageChangeNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::TTS_OnLanguageChange: {
      command.reset(new(__FILE__, __LINE__) commands::OnTTSLanguageChangeNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::Buttons_OnButtonEvent: {
      command.reset(new(__FILE__, __LINE__) commands::hmi::OnButtonEventNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::Buttons_OnButtonPress: {
      command.reset(new(__FILE__, __LINE__) commands::hmi::OnButtonPressNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::Buttons_OnButtonSubscription: {
      command.reset(new(__FILE__, __LINE__) commands::hmi::OnButtonSubscriptionNotification(
          message, application_manager));
      break;
    }
#ifdef HMI_DBUS_API
    case hmi_apis::FunctionID::VehicleInfo_SubscribeGps: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeGps>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeGps>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeSpeed: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeSpeed>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeSpeed>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeRpm: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeRpm>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeRpm>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeFuelLevel: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeFuelLevel>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeFuelLevel>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeFuelLevel_State: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeFuelLevel_State>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeFuelLevel_State>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeInstantFuelConsumption: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeInstantFuelConsumption>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeInstantFuelConsumption>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeExternalTemperature: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeExternalTemperature>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeExternalTemperature>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribePrndl: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribePrndl>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribePrndl>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeVin: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeVin>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeVin>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeTirePressure: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeTirePressure>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeTirePressure>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeOdometer: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeOdometer>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeOdometer>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeBeltStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeBeltStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeBeltStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeBodyInformation: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeBodyInformation>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeBodyInformation>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeDeviceStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeDeviceStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeDeviceStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeDriverBraking: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeDriverBraking>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeDriverBraking>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeWiperStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeWiperStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeWiperStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeHeadLampStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeHeadLampStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeHeadLampStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeEngineTorque: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeEngineTorque>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeEngineTorque>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeAccPedalPosition: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeAccPedalPosition>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeAccPedalPosition>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeSteeringWheelAngle: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeSteeringWheelAngle>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeSteeringWheelAngle>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeECallInfo: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeECallInfo>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeECallInfo>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeAirbagStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeAirbagStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeAirbagStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeEmergencyEvent: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeEmergencyEvent>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeEmergencyEvent>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeClusterModeStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeClusterModeStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeClusterModeStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_SubscribeMyKey: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeMyKey>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_SubscribeMyKey>(
            message, application_manager));
      break;
    }
#else
    case hmi_apis::FunctionID::VehicleInfo_SubscribeVehicleData: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::VISubscribeVehicleDataRequest(
            message, application_manager));
      }
      break;
    }
#endif  // #ifdef HMI_DBUS_API
#ifdef HMI_DBUS_API
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeGps: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeGps>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeGps>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeSpeed: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeSpeed>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeSpeed>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeRpm: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeRpm>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeRpm>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeFuelLevel: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeFuelLevel>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeFuelLevel>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeFuelLevel_State: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeFuelLevel_State>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeFuelLevel_State>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeInstantFuelConsumption: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::
                VehicleInfo_UnsubscribeInstantFuelConsumption>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::
                VehicleInfo_UnsubscribeInstantFuelConsumption>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeExternalTemperature: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeExternalTemperature>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeExternalTemperature>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribePrndl: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribePrndl>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribePrndl>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeVin: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeVin>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeVin>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeTirePressure: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeTirePressure>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeTirePressure>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeOdometer: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeOdometer>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeOdometer>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeBeltStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeBeltStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeBeltStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeBodyInformation: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeBodyInformation>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeBodyInformation>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeDeviceStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeDeviceStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeDeviceStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeDriverBraking: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeDriverBraking>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeDriverBraking>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeWiperStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeWiperStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeWiperStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeHeadLampStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeHeadLampStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeHeadLampStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeEngineTorque: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeEngineTorque>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeEngineTorque>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeAccPedalPosition: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeAccPedalPosition>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeAccPedalPosition>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeSteeringWheelAngle: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeSteeringWheelAngle>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeSteeringWheelAngle>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeECallInfo: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeECallInfo>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeECallInfo>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeAirbagStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeAirbagStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeAirbagStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeEmergencyEvent: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeEmergencyEvent>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeEmergencyEvent>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeClusterModeStatus: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeClusterModeStatus>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeClusterModeStatus>(
            message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeMyKey: {
      if (is_response)
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponseTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeMyKey>(
            message, application_manager));
      else
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequestTemplate<
            hmi_apis::FunctionID::VehicleInfo_UnsubscribeMyKey>(
            message, application_manager));
      break;
    }
#else
    case hmi_apis::FunctionID::VehicleInfo_UnsubscribeVehicleData: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::VIUnsubscribeVehicleDataRequest(
            message, application_manager));
      }
      break;
    }
#endif  // #ifdef HMI_DBUS_API
#ifdef HMI_DBUS_API
    case hmi_apis::FunctionID::VehicleInfo_OnGpsData: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnVIGpsDataNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnSpeed: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnVISpeedNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnRpm: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnVIRpmNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnFuelLevel: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIFuelLevelNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnFuelLevelState: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIFuelLevelStateNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnInstantFuelConsumption: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIInstantFuelConsumptionNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnExternalTemperature: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIExternalTemperatureNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnVin: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnVIVinNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnPrndl: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnVIPrndlNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnTirePressure: {
      command.reset(new(__FILE__, __LINE__) commands::OnVITirePressureNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnOdometer: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnVIOdometerNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnBeltStatus: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIBeltStatusNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnBodyInformation: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIBodyInformationNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnDeviceStatus: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIDeviceStatusNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnDriverBraking: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIDriverBrakingNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnWiperStatus: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIWiperStatusNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnHeadLampStatus: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIHeadLampStatusNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnEngineTorque: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIEngineTorqueNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnAccPedalPosition: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIAccPedalPositionNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnSteeringWheelAngle: {
      command.reset(new(__FILE__, __LINE__) commands::OnVISteeringWheelAngleNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VehicleInfo_OnMyKey: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnVIMyKeyNotification(message, application_manager));
      break;
    }
#else
    case hmi_apis::FunctionID::VehicleInfo_OnVehicleData: {
      command.reset(new(__FILE__, __LINE__) commands::OnVIVehicleDataNotification(
          message, application_manager));
      break;
    }
#endif  // #ifdef HMI_DBUS_API
    case hmi_apis::FunctionID::Navigation_OnTBTClientState: {
      command.reset(new(__FILE__, __LINE__) commands::OnNaviTBTClientStateNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::UI_OnKeyboardInput: {
      command.reset(new(__FILE__, __LINE__) commands::hmi::OnUIKeyBoardInputNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::UI_OnTouchEvent: {
      command.reset(new(__FILE__, __LINE__) commands::hmi::OnUITouchEventNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::UI_OnResetTimeout: {
      command.reset(new(__FILE__, __LINE__) commands::hmi::OnUIResetTimeoutNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::Navigation_StartStream: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::NaviStartStreamResponse(
            message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::NaviStartStreamRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_StopStream: {
      if (is_response) {
        command.reset(
            new(__FILE__, __LINE__) commands::NaviStopStreamResponse(message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::NaviStopStreamRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_StartAudioStream: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::AudioStartStreamResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::AudioStartStreamRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_StopAudioStream: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::AudioStopStreamResponse(
            message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::AudioStopStreamRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_OnAudioDataStreaming: {
      command.reset(new(__FILE__, __LINE__) commands::OnAudioDataStreamingNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::Navigation_OnVideoDataStreaming: {
      command.reset(new(__FILE__, __LINE__) commands::OnVideoDataStreamingNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::VR_PerformInteraction: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::VRPerformInteractionResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::VRPerformInteractionRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnSystemRequest: {
      command.reset(new(__FILE__, __LINE__) commands::OnSystemRequestNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnPutFile: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnPutFileNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnResumeAudioSource: {
      command.reset(new(__FILE__, __LINE__) commands::OnResumeAudioSourceNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::UI_SetDisplayLayout: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::UiSetDisplayLayoutResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::UiSetDisplayLayoutRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnSDLClose: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnSDLCloseNotification(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnSDLPersistenceComplete: {
      command.reset(new(__FILE__, __LINE__) commands::OnSDLPersistenceCompleteNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnFileRemoved: {
      command.reset(new(__FILE__, __LINE__) commands::OnFileRemovedNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::UI_OnRecordStart: {
      command.reset(new(__FILE__, __LINE__) commands::OnRecordStartdNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_SystemRequest: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::BasicCommunicationSystemResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::BasicCommunicationSystemRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_SendLocation: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::NaviSendLocationResponse(
            message, application_manager));
      } else {
        command.reset(new(__FILE__, __LINE__) commands::NaviSendLocationRequest(
            message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::SDL_AddStatisticsInfo: {
      command.reset(new(__FILE__, __LINE__) commands::AddStatisticsInfoNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::SDL_OnSystemError: {
      command.reset(new(__FILE__, __LINE__) commands::OnSystemErrorNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::SDL_OnReceivedPolicyUpdate: {
      command.reset(
          new(__FILE__, __LINE__) commands::OnReceivedPolicyUpdate(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::SDL_OnPolicyUpdate: {
      command.reset(new(__FILE__, __LINE__) commands::OnPolicyUpdate(message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::SDL_OnDeviceStateChanged: {
      command.reset(new(__FILE__, __LINE__) commands::OnDeviceStateChangedNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::TTS_OnResetTimeout: {
      command.reset(new(__FILE__, __LINE__) commands::hmi::OnTTSResetTimeoutNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_OnEventChanged: {
      command.reset(new(__FILE__, __LINE__) commands::OnEventChangedNotification(
          message, application_manager));
      break;
    }
    case hmi_apis::FunctionID::BasicCommunication_DialNumber: {
      if (is_response) {
        command.reset(new(__FILE__, __LINE__) commands::hmi::DialNumberResponse(
            message, application_manager));
      } else {
        command.reset(
            new(__FILE__, __LINE__) commands::hmi::DialNumberRequest(message, application_manager));
      }
      break;
    }
    case hmi_apis::FunctionID::Navigation_OnWayPointChange: {
      command.reset(new(__FILE__, __LINE__) commands::OnNaviWayPointChangeNotification(
          message, application_manager));
      break;
    }
  }
  return command;
}

}  // namespace application_manager
