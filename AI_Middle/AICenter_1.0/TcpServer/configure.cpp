#include "configure.h"

//\"steamid\": \"([0-9]+)\",([0-9a-z\n\t\"\s\S]+)\"player\": \{[\n\t\s\S]+\"steamid\": \"([0-9]+)\",[0-9a-z\n\t\"\s\S]+\"round_killhs\": ([0-9]+),[0-9a-z\n\t\"\s\S]+\"type\": \"Knife\",\n\t\t\t\t\"state\": \"([a-z]+)\"[0-9a-z\n\t\"\s\S]+\"kills\": ([0-9]+),\n\t\t\t\"assists\": [0-9]+,\n\t\t\t\"deaths\": ([0-9])+
QRegExp rx_Player("\\\"steamid\\\": \\\"([0-9]+)\\\",([0-9a-z\\n\\t\\\"\\s\\S]+)\\\"player\\\": \\{[\\n\\t\\s\\S]+\\\"steamid\\\": \\\"([0-9]+)\\\",[0-9a-z\\n\\t\\\"\\s\\S]+\\\"round_killhs\\\": ([0-9]+),[0-9a-z\\n\\t\\\"\\s\\S]+\\\"weapons\\\"([0-9a-z\\n\\t\\\"\\s\\S]+)\\\"kills\\\": ([0-9]+),\\n\\t\\t\\t\\\"assists\\\": [0-9]+,\\n\\t\\t\\t\\\"deaths\\\": ([0-9])+,");
QRegExp rx_Weapon("\\\"Knife\\\",\\n\\t\\t\\t\\t\\\"state\\\": \\\"([a-z]+)");