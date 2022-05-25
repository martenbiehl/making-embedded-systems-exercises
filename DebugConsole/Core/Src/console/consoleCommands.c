// ConsoleCommands.c
// This is where you add commands:
//		1. Add a protoype
//			static eCommandResult_T ConsoleCommandVer(const char buffer[]);
//		2. Add the command to mConsoleCommandTable
//		    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
//		3. Implement the function, using ConsoleReceiveParam<Type> to get the parameters from the buffer.

#include <string.h>
#include "consoleCommands.h"
#include "console.h"
#include "consoleIo.h"
#include "version.h"

#define IGNORE_UNUSED_VARIABLE(x)     if ( &x == &x ) {}
#define NOT_FOUND		              -1

static eCommandResult_T ConsoleCommandComment(const char buffer[]);
static eCommandResult_T ConsoleCommandVer(const char buffer[]);
static eCommandResult_T ConsoleCommandHelp(const char buffer[]);
static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[]);
static eCommandResult_T ConsoleCommandParamExampleHexUint16(const char buffer[]);
static eCommandResult_T ConsoleCommandTrigger(const char buffer[]);
static eCommandResult_T ConsoleCommandGetSetTemperature(const char buffer[]);
static eCommandResult_T ConsoleCommandAirQualitySensorSubSystem(const char buffer[]);

static const sConsoleCommandTable_T mConsoleCommandTable[] =
{
    {";", &ConsoleCommandComment, HELP("Comment! You do need a space after the semicolon. ")},
    {"help", &ConsoleCommandHelp, HELP("Lists the commands available")},
    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
    {"int", &ConsoleCommandParamExampleInt16, HELP("How to get a signed int16 from params list: int -321")},
    {"u16h", &ConsoleCommandParamExampleHexUint16, HELP("How to get a hex u16 from the params list: u16h aB12")},
	{"trigger", &ConsoleCommandTrigger, HELP("trigger a statemachine event: trigger eventname")},
	{"temperature", &ConsoleCommandGetSetTemperature, HELP("Get or set temperature")},
	{"air_quality_sensor", &ConsoleCommandAirQualitySensorSubSystem, HELP("Air Quality Sensor Sub System")},

	CONSOLE_COMMAND_TABLE_END // must be LAST
};

static eCommandResult_T ConsoleCommandComment(const char buffer[])
{
	// do nothing
	IGNORE_UNUSED_VARIABLE(buffer);
	return COMMAND_SUCCESS;
}

static eCommandResult_T ConsoleCommandHelp(const char buffer[])
{
	uint32_t i;
	uint32_t tableLength;
	eCommandResult_T result = COMMAND_SUCCESS;

    IGNORE_UNUSED_VARIABLE(buffer);

	tableLength = sizeof(mConsoleCommandTable) / sizeof(mConsoleCommandTable[0]);
	for ( i = 0u ; i < tableLength - 1u ; i++ )
	{
		ConsoleIoSendString(mConsoleCommandTable[i].name);
#if CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(" : ");
		ConsoleIoSendString(mConsoleCommandTable[i].help);
#endif // CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[])
{
	int16_t parameterInt;
	eCommandResult_T result;
	result = ConsoleReceiveParamInt16(buffer, 1, &parameterInt);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Parameter is ");
		ConsoleSendParamInt16(parameterInt);
		ConsoleIoSendString(" (0x");
		ConsoleSendParamHexUint16((uint16_t)parameterInt);
		ConsoleIoSendString(")");
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}
static eCommandResult_T ConsoleCommandParamExampleHexUint16(const char buffer[])
{
	uint16_t parameterUint16;
	eCommandResult_T result;
	result = ConsoleReceiveParamHexUint16(buffer, 1, &parameterUint16);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Parameter is 0x");
		ConsoleSendParamHexUint16(parameterUint16);
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandVer(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;

    IGNORE_UNUSED_VARIABLE(buffer);

	ConsoleIoSendString(VERSION_STRING);
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}


const sConsoleCommandTable_T* ConsoleCommandsGetTable(void)
{
	return (mConsoleCommandTable);
}

static eCommandResult_T ConsoleCommandTrigger(const char buffer[])
{
	char eventname[255] = {0};
	eCommandResult_T result;
	result = ConsoleReceiveParamString(buffer, 1, &eventname[0], 255);
	if ( COMMAND_SUCCESS == result )
	{
		ConsoleIoSendString("Event name is ");
		ConsoleSendString(eventname);
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static uint32_t mTemperature = 0;
void SetTemperature(uint32_t temperature)
{
	mTemperature = temperature;
}
uint32_t GetTemperature()
{
	return mTemperature;
}

static eCommandResult_T ConsoleCommandGetSetTemperature(const char buffer[])
{
	uint32_t temperature;
	eCommandResult_T result;
	result = ConsoleReceiveParamUint32(buffer, 1, &temperature);
	if ( COMMAND_SUCCESS == result )
	{
		SetTemperature(temperature);
		ConsoleIoSendString("Temperature is set to ");
		ConsoleSendParamInt32(temperature);
		ConsoleIoSendString(STR_ENDLINE);
	} else {
		temperature = GetTemperature();
		ConsoleIoSendString("Temperature is ");
		ConsoleSendParamInt32(temperature);
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandAirQualitySubSystemConnected(const char buffer[]);
static eCommandResult_T ConsoleCommandAirQualitySubSystemLast(const char buffer[]);

static const sConsoleCommandTable_T mConsoleCommandTableAirQualitySubSystem[] =
{
    {";", &ConsoleCommandComment, HELP("Comment! You do need a space after the semicolon. ")},
    {"help", &ConsoleCommandHelp, HELP("Lists the commands available")},
    {"connection", &ConsoleCommandAirQualitySubSystemConnected, HELP("Is the system connected?")},
    {"last", &ConsoleCommandAirQualitySubSystemLast, HELP("Print last data")},

	CONSOLE_COMMAND_TABLE_END // must be LAST
};

const sConsoleCommandTable_T* ConsoleCommandsGetTableAirQualitySubSystem(void)
{
	return (mConsoleCommandTableAirQualitySubSystem);
}


static eCommandResult_T ConsoleCommandAirQualitySensorSubSystem(const char buffer[])
{
	const sConsoleCommandTable_T* commandTable;
	uint32_t cmdIndex;
	int32_t  found;
	eCommandResult_T result;
	char command[255] = {0};


	commandTable = ConsoleCommandsGetTableAirQualitySubSystem();
	cmdIndex = 0u;
	found = NOT_FOUND;
	result = ConsoleReceiveParamString(buffer, 1, &command[0], 255);
	while ( ( NULL != commandTable[cmdIndex].name ) && ( NOT_FOUND == found ) )
	{
		if ( ConsoleCommandMatch(commandTable[cmdIndex].name, command) )
		{
			result = commandTable[cmdIndex].execute(command);
			if ( COMMAND_SUCCESS != result )
			{
				ConsoleIoSendString("Error: ");
				ConsoleIoSendString(command);

				ConsoleIoSendString("Help: ");
				ConsoleIoSendString(commandTable[cmdIndex].help);
				ConsoleIoSendString(STR_ENDLINE);

			}
			found = cmdIndex;
		}
		else
		{
			cmdIndex++;

		}
	}
	if ( NOT_FOUND == found )
	{
		if (strlen(buffer) > 2) /// shorter than that, it is probably nothing
		{
			ConsoleIoSendString("Command not found.");
			ConsoleIoSendString(STR_ENDLINE);
		}
	}
	return COMMAND_SUCCESS;
}

static eCommandResult_T ConsoleCommandAirQualitySubSystemConnected(const char buffer[])
{
	ConsoleIoSendString("Air Quality Subsystem is ");
	ConsoleIoSendString("not ");
	ConsoleIoSendString("connected");
	ConsoleIoSendString(STR_ENDLINE);

	return COMMAND_SUCCESS;
}

static eCommandResult_T ConsoleCommandAirQualitySubSystemLast(const char buffer[])
{
	ConsoleIoSendString("Air Quality Subsystem last data: ");
	ConsoleIoSendString(STR_ENDLINE);

	ConsoleIoSendString("temperature: ");
	ConsoleSendParamInt32(GetTemperature());
	ConsoleIoSendString("deg C");
	ConsoleIoSendString(STR_ENDLINE);

	ConsoleIoSendString("humidity: ");
	ConsoleSendParamInt32(20);
	ConsoleIoSendString("%");
	ConsoleIoSendString(STR_ENDLINE);

	return COMMAND_SUCCESS;
}

