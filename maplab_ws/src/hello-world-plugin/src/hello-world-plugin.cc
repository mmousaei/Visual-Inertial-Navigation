#include <iostream>
#include <string>
#include <map-manager/map-manager.h>
#include <vi-map/vi-map.h>

#include <console-common/console-plugin-base.h>

// Your new plugin needs to derive from ConsolePluginBase.
// (Alternatively, you can derive from ConsolePluginBaseWithPlotter if you need
// RViz plotting abilities for your VI map.)
class HelloWorldPlugin : public common::ConsolePluginBase {
 public:
  // Every plugin needs to implement a getPluginId function which returns a
  // string that gives each plugin a unique name.
  std::string getPluginId() const override {
    return "hello_world_plugin";
  }

  // The constructor takes a pointer to the Console object which we can forward
  // to the constructor of ConsolePluginBase.
  HelloWorldPlugin(common::Console* console)
      : common::ConsolePluginBase(console) {
    // You can add your commands in here.
    addCommand(
        {"hello_world", "hello"},  // Map "hello_world" and "hello" to this
                                   // command.
        [this]() -> int {  // Function to call when this command is entered.
          // This function can do anything you want. Check the other plugins
          // under ~/maplab_ws/src/maplab/console-plugins for more examples.

          // Here, we just print a message to the terminal.
          std::cout << "Hello world!" << std::endl;

          // Every console command returns an integer, you can take one from
          // the CommandStatus enum. kSuccess returns everything is fine.
          // Other commonly used return values are common::kUnknownError and
          // common::kStupidUserError.
          return common::kSuccess;
        },

        // This is the description of your command. This will get printed when
        // you run `help` in the console.
        "This command prints \"Hello World!\" to the console.",

        // This specifies the execution method of your command. For most
        // commands, it is sufficient to run them in sync with
        // common::Processing::Sync.
        common::Processing::Sync);
  
         addCommand(
        {"my_vi_map_command"},

        [this]() -> int {
          // Get the currently selected map.
          std::string selected_map_key;

          // This function will write the name of the selected map key into
          // selected_map_key. The function will return false and print an error
          // message if no map key is selected.
          if (!getSelectedMapKeyIfSet(&selected_map_key)) {
            return common::kStupidUserError;
          }

          // Create a map manager instance.
          vi_map::VIMapManager map_manager;

          // Get and lock the map which blocks all other access to the map.
          vi_map::VIMapManager::MapWriteAccess map =
              map_manager.getMapWriteAccess(selected_map_key);

          // Now run your algorithm on the VI map.
          // E.g., we can get the number of missions and print it.
          const size_t num_missions = map->numMissions();
          std::cout << "The VI map " << selected_map_key << " contains "
                    << num_missions << " missions." << std::endl;

          return common::kSuccess;
        },

        "This command will run an awesome VI map algorithm.",
        common::Processing::Sync);
  }
};

// Finally, call the MAPLAB_CREATE_CONSOLE_PLUGIN macro to create your console
// plugin.
MAPLAB_CREATE_CONSOLE_PLUGIN(HelloWorldPlugin);