# API
This document provides details on custom actions designed for integration with Home Assistant, including their usage, parameters, and examples.

## Summary
- [Action Documentation](#action-documentation)
  - [Button Action (`button`)](#button-action-button): Configures properties and state of buttons on a specified button page.
  - [Command Action (`command`)](#command-action-command): Sends a custom command directly to the display.
  - [Component Action (`component`)](#component-action-component): Updates a display component text/icon, color, font and visibility.
  - [Component Value Action (`component_val`)](#component-value-action-component_val): Updates the value of a specified component on the display.
  - [Entity Details Show Action (`entity_details_show`)](#entity-details-show-action-entity_details_show): Displays detailed information for a specific entity.
  - [Notification Clear Action (`notification_clear`)](#notification-clear-action-notification_clear): Clears the current notification from the screen.
  - [Notification Show Action (`notification_show`)](#notification-show-action-notification_show): Displays a notification-message on the screen.
  - [QR Code Action (`qrcode`)](#qr-code-action-qrcode): Displays a QR code on the panel or updates the QR code information for local control.
  - [RTTTL Play Action (`rtttl_play`)](#rtttl-play-action-rtttl_play): Plays melodies encoded in the RTTTL format.
  - [Upload TFT Action (`upload_tft`)](#tft-file-update-action-upload_tft): Enables TFT file updates from a URL, requiring the "Upload TFT" add-on.
  - [Utilities Group Refresh Action (`utilities_group_refresh`)](#utilities-group-refresh-action-utilities_group_refresh): Updates utility group display values and direction indicators.
  - [Wake Up Action (`wake_up`)](#wake-up-action-wake_up): Activates the display from a screensaver or low-brightness state.
  - [Alarm Settings Page Action (`page_alarm`)](#alarm-settings-page-action-page_alarm): Updates the Alarm page with current state information.
  - [Climate Page Action (`page_climate`)](#climate-page-action-page_climate): Updates the Climate page with current state information.
  - [Media Player Page Action (`page_media_player`)](#media-player-page-action-page_media_player): Updates the Media Player page with current state information.
- [Screen Components](#screen-components)
  - [Home page - Chips](#home-page---chips)
    - [User-defined Chips](#user-defined-chips)
    - [Relays Chips](#relays-chips)
    - [Climate Chip](#climate-chip)
  - [Home page - Custom Buttons](#home-page---custom-buttons)
  - [Home page - Values](#home-page---values)
  - [Entities Pages - Values](#entities-pages---values)

## Action Documentation

### General Guidance
In general, there's no validation on the content of the parameters in a action call.
Please make sure to fulfill the validation from the action caller side, otherwise it can drive to a crash in the ESPHome side, it will most likely restart the panel.

One example is with colors. In almost all cases, it is expected an array with 3 unsigned integers between 0 to 255.
If you send anything different, the conversion to the RGB565 used by Nextion will crash.

### Table of Contents
<!-- markdownlint-disable MD013 -->
| Action ID | Action Name | Description |
|------------|--------------|-------------|
| [`button`](#button-action-button) | [Button Action](#button-action-button) | Configures properties and state of buttons on a specified button page. |
| [`command`](#command-action-command) | [Command Action](#command-action-command) | Sends a custom command directly to the display. |
| [`component`](#component-action-component) | [Component Action](#component-action-component) | Updates a display component text/icon, color, font and visibility. |
| [`component_val`](#component-value-action-component_val) | [Component Value Action](#component-value-action-component_val) | Updates the value of a specified component on the display. |
| [`entity_details_show`](#entity-details-show-action-entity_details_show) | [Entity Details Show Action](#entity-details-show-action-entity_details_show) | Displays detailed information for a specific entity. |
| [`notification_clear`](#notification-clear-action-notification_clear) | [Notification Clear Action](#notification-clear-action-notification_clear) | Clears the current notification from the screen. |
| [`notification_show`](#notification-show-action-notification_show) | [Notification Show Action](#notification-show-action-notification_show) | Displays a notification-message on the screen. |
| [`page_alarm`](#alarm-settings-page-action-page_alarm) | [Alarm Settings Page Action](#alarm-settings-page-action-page_alarm) | Updates the Alarm page with current state information. |
| [`page_climate`](#climate-page-action-page_climate) | [Climate Page Action](#climate-page-action-page_climate) | Updates the Climate page with current state information. |
| [`page_media_player`](#media-player-page-action-page_media_player) | [Media Player Page Action](#media-player-page-action-page_media_player) | Updates the Media Player page with current state information. |
| [`qrcode`](#qr-code-action-qrcode) | [QR Code Action](#qr-code-action-qrcode) | Displays a QR code on the panel or update the QR code information for local control. |
| [`rtttl_play`](#rtttl-play-action-rtttl_play) | [RTTTL Play Action](#rtttl-play-action-rtttl_play) | Plays melodies encoded in the RTTTL format. |
| [`upload_tft`](#tft-file-update-action-upload_tft) | [Upload TFT Action](#tft-file-update-action-upload_tft) | Enables TFT file updates from a URL, requiring the "Upload TFT" add-on. |
| [`utilities_group_refresh`](#utilities-group-refresh-action-utilities_group_refresh) | [Utilities Group Refresh Action](#utilities-group-refresh-action-utilities_group_refresh) | Updates utility group display values and direction indicators. |
| [`wake_up`](#wake-up-action-wake_up) | [Wake Up Action](#wake-up-action-wake_up) | Activates the display from a screensaver or low-brightness state. |
<!-- markdownlint-enable MD013 -->

### Button Action: `button`
Configures the properties and state of buttons on a specified button page, allowing for dynamic updates to button appearance and behavior based on specified parameters.

**Usage:**
This action is designed for dynamic user interface adjustments, enabling the customization of button states, icons, colors, and labels.
It's particularly useful for reflecting changes in device states or user interactions within the UI.

**Parameters:**
- 'id' (uint8_t): The unique button's identifier (1 to 32)
- `page` (string): The page identifier where the button is located.
- `component` (string): The button's unique identifier.
- `state` (bool): The state of the button, which can affect its background picture and other visual elements.
- `icon` (string): Icon codepoint from [HASwitchPlate Material Design Icons](https://htmlpreview.github.io/?https://github.com/jobr99/Generate-HASP-Fonts/blob/master/cheatsheet.html).
Example: "\uE6E8" for `mdi:lightbulb-on-outline`.
- `icon_color` (int[]): The RGB color array for the icon.
- `icon_font` (int): The Nextion font identifier for the icon (default is 8).
- `bri` (string): Brightness level or other dynamic information to display on the button close to the icon.
- `label` (string): The main text label displayed on the button.

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_button
data:
  id: 8
  page: "buttonpage01"
  component: "button08"
  state: true
  icon: "\uE6E8"           # Example for mdi:lightbulb-on-outline
  icon_color: [255, 0, 0]  # Red
  icon_font: 2
  bri: "75%"
  label: "Living Room"
```
> [!NOTE]
> Replace `<your_panel_name>` with the specific name of your panel configured in Home Assistant.
> This action dynamically updates the specified button's properties to match the provided parameters.

### Command Action: `command`
Sends a custom command directly to the display, enabling direct interaction and dynamic content updates.

**Usage:**
This action is particularly useful for advanced customizations and direct display manipulations, such as showing messages, updating statuses, or any other display-centric commands.

**Parameters:**
- `cmd` (string): The command string to be sent to the display. Please refer to [The Nextion Instruction Set](https://nextion.tech/instruction-set/) for a comprehensive list of commands supported.

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_command
data:
  cmd: "page home"  # Go to page "Home"
```

> [!NOTE]
> Replace `<your_panel_name>` with your specific panel name as configured in Home Assistant to ensure correct action execution.
>
> Ensure the command string (`cmd`) is properly formatted according to your display's command processing capabilities.

### Component Action: `component`
Updates a display component text (or icon), color, font size, and visibility within Home Assistant.

**Usage:**
This action is ideal for dynamically updating icons on your Panel, allowing for a customizable and interactive user interface.

**Parameters:**
- `page` (string): Identifies the page where the component belongs to.
- `component` (string): Identifier of the chip or button component. Refer to "[Screen components](#screen-components)" for more details.
- `txt` (string): Text to display or icon codepoint from [HASwitchPlate Material Design Icons](https://htmlpreview.github.io/?https://github.com/jobr99/Generate-HASP-Fonts/blob/master/cheatsheet.html).
Example: "\uE6E8" for `mdi:lightbulb-on-outline`.
- `color` (int[]): RGB color array for the icon. Example: `[0, 255, 0]` for green.
- `font` (int): The Nextion font id to be used. Select `-1` to not change the current font.
- `visible` (bool): Flag indicating whether the icon should be visible (`true`) or hidden (`false`).

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_component
data:
  page: home
  component: chip03
  txt: "\uE6E8"      # Example for mdi:lightbulb-on-outline
  color: [0, 255, 0]  # Green
  font: 8
  visible: true
```
> [!NOTE]
> Ensure the placeholder `<your_panel_name>` is replaced with the specific panel name you will need to reference in your Home Assistant configuration.

### Component Value Action: `component_val`
Updates the value of a specified component on the display, enabling dynamic value updates.

**Usage:**
Ideal for interfaces requiring real-time updates of numerical values, such as counters, temperature readings, or any numeric indicators.

**Parameters:**
- `page` (string): The page identifier where the component is located.
- `component` (string): Identifier of the component whose value will be updated. It's crucial this matches the component's ID in your display layout accurately.
- `val` (int): The new integer value to be set for the component. This can represent various data types, depending on the component's purpose (e.g., temperature, humidity levels).

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_component_val
data:
  page: cover
  component: coverslider
  val: 25
```
> [!NOTE]
> Replace `<your_panel_name>` with your specific panel name as configured in Home Assistant to ensure correct action execution.
>
> Ensure the `component` accurately matches the component on your display to successfully update its value.

### Entity Details Show Action: `entity_details_show`
This action is designed to display detailed information about a specific entity within the panel's interface.
It enables users to navigate to a dedicated page showing extensive details about an entity, such as a light or a climate,
and provides a structured way to return to either the home page or a specific button page.

**Usage:**
Ideal for interfaces requiring detailed entity information across various contexts.
By specifying the `entity` and `back_page`, users are offered a seamless navigation experience,
ensuring they can easily access detailed information and return to their initial navigation point within the interface.

**Parameters:**
- `entity_id` (string): The unique identifier of the entity (`entity_id` in Home Assistant) for which details are displayed.
- `back_page` (string): The page identifier to return to after viewing entity details.
Valid options are `home` for the home page or `buttonpage01` to `buttonpage04` for button pages.
No other pages are supported to maintain navigation consistency.

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_entity_details_show
data:
  entity_id: "light.living_room"
  back_page: "buttonpage01"
```
> [!NOTE]
> Ensure to replace <your_panel_name> with the specific name of your panel configured in Home Assistant.
> This setup provides a direct and user-friendly way to access and return from detailed entity information, enhancing the interface's usability.

### Notification Clear Action: `notification_clear`
Removes any displayed notification from the screen, allowing the display to return to its normal state or view.

**Usage:**
This action is essential after displaying notifications or alerts.
It ensures the user interface remains clean and uncluttered by clearing messages once they are no longer needed or have been acknowledged.

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_notification_clear
```
> [!NOTE]
> Replace `<your_panel_name>` with the specific name of your panel configured in Home Assistant to ensure the action executes correctly.
This simple action clears the current notification from the display, maintaining a tidy interface.

### Notification Show Action: `notification_show`
Displays a notification message on the screen, enabling dynamic presentation of information or alerts.

**Usage:**
Designed for scenarios requiring immediate feedback or notification on the display,
this action is suitable for showing alerts, informational messages, or updates directly on the screen interface.

**Parameters:**
- `label` (string): A brief title or label for the notification, typically displayed in a prominent, bold format.
- `message` (string): The detailed message or content of the notification, providing the main information or alert to the user.
The system will automatically wrap text to fit the display unless `\r` is used to insert manual line breaks. When `\r` is present,
the system respects only the line breaks provided by the user, enhancing message formatting control.

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_notification_show
data:
  label: "Security Alert"
  message: "Front door opened at 10:30 PM\rPlease check the entrance."
```
> [!NOTE]
> Replace `<your_panel_name>` with the specific name of your panel configured in Home Assistant.
> The action ensures the action executes correctly, displaying the notification with the specified `label` and `message`.
>
> Utilize `\r` within the message for custom line breaks, offering precise formatting control.

### Alarm Settings Page Action: `page_alarm`
Populates the alarm settings page with the current configuration and state information,
seamlessly integrating with the panel's interface to reflect the latest settings and statuses of the alarm system.

**Usage:**
The `page_alarm` action is specifically designed to dynamically update the alarm settings page, providing users with immediate access to the alarm system's controls and information.
It plays a crucial role in ensuring a responsive and user-friendly interface for alarm management, allowing for real-time interaction with the alarm system directly from the panel.

**Parameters:**
- `page_title` (string): The title displayed at the top of the alarm settings page.
- `state` (string): The current state of the alarm system, such as "armed_home" or "disarmed".
- `supported_features` (int): A bitmask indicating the features supported by the alarm system.
This determines the controls and options available on the alarm settings page.
The bitmask values are aligned with the
[Home Assistant Alarm Control Panel Supported Features](https://github.com/home-assistant/core/blob/33ff6b5b6ee3d92f4bb8deb9594d67748ea23d7c/homeassistant/components/alarm_control_panel/const.py#L32).
- `code_format` (string): Specifies the code format required for arming/disarming the alarm system, such as numeric or alphanumeric.
- `code_arm_required` (bool): Indicates whether a code is required to arm the system.
- `entity` (string): The entity ID of the alarm system, used for state updates and control actions.
- `mui_alarm` (string[]): An array of localized text strings for the alarm control buttons, supporting various alarm states and actions.

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_page_alarm
data:
  page_title: "Home Security System"
  state: "disarmed"
  supported_features: 31  # Example: Supports arm/disarm, home/away modes, etc.
  code_format: "number"
  code_arm_required: true
  entity: "alarm_control_panel.home_alarm"
  mui_alarm:
    - "Zuhause"
    - "Abwesend"
    - "Nacht"
    - "Urlaub"
    - "Umgehen"
    - "Entwaffnen"
```
> [!NOTE]
> Ensure to replace `<your_panel_name>` with the actual name of your panel configured in Home Assistant.
> This action configuration allows for the alarm settings page to dynamically reflect the current features, state, and control options of your alarm system, enhancing the overall user experience.

### Climate Page Action: `page_climate`
Updates the climate page with the current state information, seamlessly integrating with the panel's interface to display the latest climate settings and statuses.

**Usage:**
Designed to dynamically update the climate page, this action ensures users have instant access to climate control settings and information.
It's crucial for maintaining a responsive and informative interface for efficient climate management.

**Parameters:**
- `current_temp` (float): The current temperature.
- `supported_features` (int): Bitmask indicating the climate device's supported features.
These features determine the available climate controls and settings on the device.
The bitmask values correspond to features such as temperature control, mode setting, fan speed adjustment, etc., as defined in Home Assistant's climate component constants.
For detailed descriptions of each feature and its corresponding bitmask value, refer to the
[Home Assistant Climate Component Constants](https://github.com/home-assistant/core/blob/33ff6b5b6ee3d92f4bb8deb9594d67748ea23d7c/homeassistant/components/climate/const.py#L156C7-L156C27).
- `target_temp` (float): The set target temperature.
- `target_temp_high` (float): The high end of the target temperature range, for devices that support temperature ranges.
- `target_temp_low` (float): The low end of the target temperature range.
- `temp_step` (int): Increment step for temperature adjustment, effectively the granularity of temperature change allowed.
- `total_steps` (int): Total number of steps for temperature adjustment, calculated as ((temp_max - temp_min) / temp_step).
- `temp_offset` (int): Offset applied to the temperature reading for calibration.
- `climate_icon` (string): Icon representing the current climate status,
selected from [HASwitchPlate Material Design Icons](https://htmlpreview.github.io/?https://github.com/jobr99/Generate-HASP-Fonts/blob/master/cheatsheet.html).
- `embedded_climate` (bool): Flag indicating if climate controls are embedded within the interface.
- `entity` (string): Entity ID for the climate device.

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_page_climate
data:
  current_temp: 22.5
  supported_features: 1 | 4  # Assuming '1' is for temperature control and '4' is for fan mode, as an example.
  target_temp: 24.0
  target_temp_high: 25.0
  target_temp_low: 19.0
  temp_step: 5               # Adjust in 0.5°C increments.
  total_steps: 56            # Calculated based on the device's temperature range and step.
  temp_offset: 70            # Applied as a calibration offset.
  climate_icon: "\uE392"     # mdi:thermostat
  embedded_climate: true
  entity: "climate.living_room"
  ```
  > [!NOTE]
> Replace `<your_panel_name>` with the specific name of your panel configured in Home Assistant.
> This action ensures the climate page reflects the latest in climate control settings, enhancing the user experience by providing up-to-date information.

### Media Player Page Action: `page_media_player`
Updates the media player page with current configuration and state information,
integrating seamlessly with the panel's interface to display the latest media playback status and controls.

**Usage:**
The `page_media_player` action is specifically tailored to dynamically update the media player page, ensuring users have immediate access to media playback controls and information.
This action is essential for providing a responsive and user-friendly interface for media management, allowing real-time interaction with the media player directly from the panel.

**Parameters:**
- `entity` (string): The entity ID of the media player.
- `state` (string): The current state of the media player (e.g., playing, paused, stopped).
- `is_volume_muted` (bool): Indicates whether the volume is currently muted.
- `friendly_name` (string): The friendly name of the media player to be displayed as the page title.
- `volume_level` (int): The current volume level of the media player.
- `media_title` (string): The title of the currently playing media.
- `media_artist` (string): The artist of the currently playing media.
- `media_duration` (float): The total duration of the currently playing media in seconds.
- `media_position` (float): The current playback position within the media in seconds.
- `media_position_delta` (float): The amount of time in seconds since the last update of the media position.
- `supported_features` (int): A bitmask indicating the features supported by the media player, such as play/pause, next/previous track, volume control, etc.
The bitmask values correspond to the
[Home Assistant Media Player Supported Features](https://github.com/home-assistant/core/blob/33ff6b5b6ee3d92f4bb8deb9594d67748ea23d7c/homeassistant/components/media_player/const.py#L177).

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_page_media_player
data:
  entity: "media_player.living_room"
  state: "playing"
  is_volume_muted: false
  friendly_name: "Living Room Player"
  volume_level: 40
  media_title: "Favorite Song"
  media_artist: "Famous Artist"
  media_duration: 180
  media_position: 30
  media_position_delta: 0.5
  supported_features: 84  # Example: Play, Pause, Next, Previous
```
> [!NOTE]
> Replace `<your_panel_name>` with the specific name of your panel configured in Home Assistant.
> This action ensures the media player page reflects the latest in media playback settings and status, enhancing the user experience by providing up-to-date information.

### QR Code Action: `qrcode`
Displays a QR code on the display, which can be used for various purposes such as sharing a WiFi password or linking to a website.

**Usage:**
This action enables the dynamic display of QR codes on a specified page of the ESPHome user interface, allowing for the convenient sharing of information.
It's particularly useful for settings where quick, scannable access to data is beneficial.

**Parameters:**
- `title` (string): The title or heading to display above the QR code, providing context or instructions.
- `qrcode` (string): The actual data or URL to be encoded into the QR code.
- `show` (bool): A flag that determines whether to immediately display the QR code page upon calling the action.

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_qrcode
data:
  title: "Wi-Fi Access"
  qrcode: "WIFI:T:WPA;S:mynetwork;P:mypass;;"
  show: true
```
<!-- markdownlint-disable MD028 -->
> [!NOTE]
> Replace `<your_panel_name>` with the specific name of your panel configured in Home Assistant.
> This action will generate and display the QR code based on the provided data, navigating to the QR code page if `show` is set to `true`.

> [!NOTE]
> This action is typically invoked during initialization to preload QR Code information based on blueprint settings,
> ensuring the data is accessible on the panel even without Wi-Fi connectivity.
> To update the QR Code information without immediately displaying it, call this action with `show: false`.
> This allows for seamless updates to the QR Code content without disrupting the current user interface.
<!-- markdownlint-enable MD028 -->

### RTTTL Play Action: `rtttl_play`
Plays melodies encoded in the RTTTL format, enabling the integration of audio feedback or alerts with simple text-based melody strings.

**Usage:**
This action is perfect for projects requiring audio signals, such as notifications, alerts, or simple melodies, by interpreting RTTTL (Ring Tone Text Transfer Language) strings.
RTTTL is a compact format for storing melody sequences in a text-based format, making it ideal for simple audio devices like buzzers.

**Parameters:**
- `tone` (string): The RTTTL string representing the melody to be played.
This string must conform to the RTTTL format, which includes the melody's name, default settings, and a sequence of notes. 

**Example Tones:**
For example tones and further inspiration, you can visit examples of RTTTL songs [here](https://codebender.cc/sketch:109888#RTTTL%20Songs.ino).

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_rtttl_play
data:
  tone: "The Simpsons:d=4,o=5,b=160:c.6,e6,f#6,8a6,g.6,e6,c6,8a,8f#,8f#,8f#,2g,8p,8p,8f#,8f#,8f#,8g,a#.,8c6,8c6,8c6,c6"
```
> [!NOTE]
> Replace `<your_panel_name>` with your specific panel name as configured in Home Assistant to ensure correct action execution.
>
> Ensure the `tone` parameter contains a valid RTTTL string to successfully play the melody.

### TFT File Update Action: `upload_tft`
Enables the remote update of the panel's TFT file from a specified URL or a default location, available exclusively with the "Upload TFT" add-on installed.
This action is valuable for downloading alternative TFT files for customization or addressing file access issues.

**Usage:**
This action is crucial for dynamically updating the TFT file, facilitating seamless transitions between different configurations or updates.
It's particularly useful for applying custom interface designs or updates when direct access to the repository is limited.

**Parameters:**
- `url` (string): The URL for downloading the TFT file.
If set to "default", it utilizes the URL from the "**Update TFT - Display Model**" selection in Home Assistant (**Settings** > **Devices & Actions** > **ESPHome**).

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_upload_tft
data:
  url: "http://homeassistant.local:8123/local/custom_tft_file.tft"  # URL to the new TFT file
```
<!-- markdownlint-disable MD028 -->
> [!NOTE]
> Replace `<your_panel_name>` with your specific panel name as configured in Home Assistant.
> Using "default" fetches the URL associated with the selected display model in Home Assistant settings, simplifying updates or customizations.

> [!IMPORTANT]
> The "Upload TFT" add-on must be installed for this action to be available, enhancing the panel's flexibility for interface customization or troubleshooting.
<!-- markdownlint-enable MD028 -->

### Utilities Group Refresh Action: `utilities_group_refresh`
Updates utility group display values and direction indicators on the panel. This action is used to refresh the displayed values for utility groups dynamically.

**Usage:**
This action is particularly useful for updating display elements associated with utility groups, such as values and directional indicators, based on specified parameters.

**Parameters:**
- `group_id` (string): The unique identifier for the utility group.
- `value1` (string): The first value to be displayed for the group.
- `value2` (string): The second value to be displayed for the group.
- `direction` (int): The direction indicator value for the group.
- `constructor` (bool): A flag to indicate if this is a constructor call, which forces updates regardless of current values.

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_utilities_group_refresh
data:
  group_id: "home"
  value1: "100 kWh"
  value2: "26 °C"
  direction: 1
  constructor: false
```
> [!NOTE]
> Replace `<your_panel_name>` with the specific name of your panel configured in Home Assistant to ensure correct action execution.

This action updates utility group display elements with the specified values and direction indicators dynamically.

### Wake Up Action: `wake_up`
Activates the display from a screensaver or low-power state, enabling dynamic interface adjustments based on user interactions or automated triggers.

**Usage:**
Ideal for scenarios requiring the display to become active upon certain events, such as motion detection, thereby conserving energy while ensuring the display is available when needed.

**Parameters:**
- `reset_timer` (bool): Determines whether to reset the sleep and dimming timers upon waking up the display.
Setting this to `true` ensures the display remains active during user presence, while `false` retains the existing timer durations.

**Home Assistant Example:**
```yaml
action: esphome.<your_panel_name>_wake_up
data:
  reset_timer: true
```
> [!NOTE]
> Replace `<your_panel_name>` with the specific name of your panel configured in Home Assistant.
> This action ensures the action is executed correctly, waking the display and optionally resetting timers based on the reset_timer parameter.

**Practical Use Case: Motion Sensor Activation:**
This action can be seamlessly integrated with a motion sensor to wake the display when motion is detected, making it instantly usable.
Additionally, if the display is already awake, calling this action with `reset_timer: true` can reset the sleep timer,
keeping the display active as long as there is movement and allowing it to sleep normally once no motion is detected.

The example bellow integrates the `wake_up` action with a motion sensor to ensure the display wakes or remains awake during periods of activity, reverting to sleep mode after inactivity.

```yaml
automation:
  - alias: "Wake Display on Motion"
    trigger:
      - platform: state
        entity_id: binary_sensor.motion_sensor_123
        to: 'on'
    action:
      - action: esphome.<your_panel_name>_wake_up
        data:
          reset_timer: true
    mode: restart
```
> [!NOTE]
> Adjust `<your_panel_name>` and `binary_sensor.motion_sensor_123` to your actual panel and sensor entity IDs.
> This setup ensures the display is responsive to environmental conditions, enhancing user interaction while managing energy consumption efficiently.

## Screen components

### Home Page - Chips
![Image](pics/Nextion_Components_Home_Chips_EU.png)
![Image](pics/Nextion_Components_Home_Chips_US.png)

#### User-defined Chips
- **Description**: Chips are icons that are shown in specific situations or hidden. Their behaviour is controlled by the blueprint.
- **Type**: Icon only with no touch commands.
- **Availability**: Global (available even when page is not visible).
- **Ids**: `home.chip01` to `home.chip07`.

#### Relays Chips
- **Description**: Icons representing each of the relays states.
- **Type**: Icon only with no touch commands.
- **Availability**: Global (available even when page is not visible).
- **Ids**: `home.chip_relay1` and `home.chip_relay2`.

#### Climate Chip
- **Description**: Icon representing the state of the main climate entity.
- **Type**: Icon only with no touch commands.
- **Availability**: Global (available even when page is not visible).
- **Ids**: `home.chip_climate`.

### Home Page - Custom buttons
![Image](pics/Nextion_Components_Home_Custom_Buttons_EU.png)
![Image](pics/Nextion_Components_Home_Custom_Buttons_US.png)

### Home Page - Values
![Image](pics/Nextion_Components_Home_Values_EU.png)
![Image](pics/Nextion_Components_Home_Values_US.png)
This is a multi-component system, with names `value01` to `value03` containing the state of the entity,
where `value01_icon` to `value03_icon` supports the icons.

### Entities Pages - Values
Just like in "[Home Page - Values](#home-page---values)", this is a multi-component system, with names `value01` to `value08` containing the state of the entity,
where `value01_icon` to `value08_icon` supports the icons and, exclusivelly in the Entities pages, `value01_label` to `value08_label`,
which will contain the friendly name or some alternative label for the entities.
