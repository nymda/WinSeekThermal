#include <wtypes.h>
#include <iostream>
#include "setupapi.h"
#include <tchar.h>
#include "seekhandler.h"
#include "strsafe.h"
#include "winreg.h"
//#include "uuids.h"
#include "setupApiFuncs.h"
#include <sstream>
#include "atlconv.h"
#include "rpcdce.h"
#include "winusb.h"
#include <fstream>

//typedef bool(__stdcall* WinUsb_Initialize)(_In_  HANDLE DeviceHandle, _Out_ PWINUSB_INTERFACE_HANDLE InterfaceHandle);
//typedef bool(__stdcall* WinUsb_Free)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle);
//typedef bool(__stdcall* WinUsb_GetAssociatedInterface)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR AssociatedInterfaceIndex, _Out_ PWINUSB_INTERFACE_HANDLE AssociatedInterfaceHandle);
//typedef bool(__stdcall* WinUsb_GetDescriptor)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR DescriptorType, _In_  UCHAR Index, _In_  USHORT LanguageID, _Out_writes_bytes_to_opt_(BufferLength, *LengthTransferred) PUCHAR Buffer, _In_  ULONG BufferLength, _Out_ PULONG LengthTransferred);
//typedef bool(__stdcall* WinUsb_QueryInterfaceSettings)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR AlternateInterfaceNumber, _Out_ PUSB_INTERFACE_DESCRIPTOR UsbAltInterfaceDescriptor);
//typedef bool(__stdcall* WinUsb_QueryDeviceInformation)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  ULONG InformationType, _Inout_ PULONG BufferLength, _Out_writes_bytes_(*BufferLength) PVOID Buffer);
//typedef bool(__stdcall* WinUsb_SetCurrentAlternateSetting)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR SettingNumber);
//typedef bool(__stdcall* WinUsb_GetCurrentAlternateSetting)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _Out_ PUCHAR SettingNumber);
//typedef bool(__stdcall* WinUsb_QueryPipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR AlternateInterfaceNumber, _In_  UCHAR PipeIndex, _Out_ PWINUSB_PIPE_INFORMATION PipeInformation);
//typedef bool(__stdcall* WinUsb_QueryPipeEx)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR AlternateSettingNumber, _In_  UCHAR PipeIndex, _Out_ PWINUSB_PIPE_INFORMATION_EX PipeInformationEx);
//typedef bool(__stdcall* WinUsb_SetPipePolicy)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID, _In_  ULONG PolicyType, _In_  ULONG ValueLength, _In_reads_bytes_(ValueLength) PVOID Value);
//typedef bool(__stdcall* WinUsb_GetPipePolicy)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID, _In_  ULONG PolicyType, _Inout_ PULONG ValueLength, _Out_writes_bytes_(*ValueLength) PVOID Value);
//typedef bool(__stdcall* WinUsb_ReadPipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID, _Out_writes_bytes_to_opt_(BufferLength, *LengthTransferred) PUCHAR Buffer, _In_  ULONG BufferLength, _Out_opt_ PULONG LengthTransferred, _In_opt_ LPOVERLAPPED Overlapped);
//typedef bool(__stdcall* WinUsb_WritePipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID, _In_reads_bytes_(BufferLength) PUCHAR Buffer, _In_  ULONG BufferLength, _Out_opt_ PULONG LengthTransferred, _In_opt_ LPOVERLAPPED Overlapped);
//typedef bool(__stdcall* WinUsb_ControlTransfer)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  WINUSB_SETUP_PACKET SetupPacket, _Out_writes_bytes_to_opt_(BufferLength, *LengthTransferred) PUCHAR Buffer, _In_  ULONG BufferLength, _Out_opt_ PULONG LengthTransferred, _In_opt_  LPOVERLAPPED Overlapped);
//typedef bool(__stdcall* WinUsb_ResetPipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID);
//typedef bool(__stdcall* WinUsb_AbortPipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID);
//typedef bool(__stdcall* WinUsb_FlushPipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID);
//typedef bool(__stdcall* WinUsb_SetPowerPolicy)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  ULONG PolicyType, _In_  ULONG ValueLength, _In_reads_bytes_(ValueLength) PVOID Value);
//typedef bool(__stdcall* WinUsb_GetPowerPolicy)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  ULONG PolicyType, _Inout_ PULONG ValueLength, _Out_writes_bytes_(*ValueLength) PVOID Value);
//typedef bool(__stdcall* WinUsb_GetOverlappedResult)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  LPOVERLAPPED lpOverlapped, _Out_ LPDWORD lpNumberOfBytesTransferred, _In_ bool bWait);
//typedef bool(__stdcall* WinUsb_GetCurrentFrameNumber)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _Out_ PULONG CurrentFrameNumber, _Out_ LARGE_INTEGER* TimeStamp);
//typedef bool(__stdcall* WinUsb_GetAdjustedFrameNumber)(_Inout_ PULONG CurrentFrameNumber, _In_  LARGE_INTEGER TimeStamp);
//typedef bool(__stdcall* WinUsb_RegisterIsochBuffer)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID, _Inout_updates_bytes_(BufferLength) PUCHAR Buffer, _In_  ULONG BufferLength, _Out_ PWINUSB_ISOCH_BUFFER_HANDLE IsochBufferHandle);
//typedef bool(__stdcall* WinUsb_UnregisterIsochBuffer)(_In_  WINUSB_ISOCH_BUFFER_HANDLE IsochBufferHandle);
//typedef bool(__stdcall* WinUsb_WriteIsochPipe)(_In_  WINUSB_ISOCH_BUFFER_HANDLE BufferHandle, _In_  ULONG Offset, _In_  ULONG Length, _Inout_ PULONG FrameNumber, _In_opt_ LPOVERLAPPED Overlapped);
//typedef bool(__stdcall* WinUsb_ReadIsochPipe)(_In_  WINUSB_ISOCH_BUFFER_HANDLE BufferHandle, _In_  ULONG Offset, _In_  ULONG Length, _Inout_ PULONG FrameNumber, _In_  ULONG NumberOfPackets, _Out_writes_(NumberOfPackets) PUSBD_ISO_PACKET_DESCRIPTOR IsoPacketDescriptors, _In_opt_ LPOVERLAPPED Overlapped);
//typedef bool(__stdcall* WinUsb_WriteIsochPipeAsap)(_In_  WINUSB_ISOCH_BUFFER_HANDLE BufferHandle, _In_  ULONG Offset, _In_  ULONG Length, _In_  bool ContinueStream, _In_opt_ LPOVERLAPPED Overlapped);
//typedef bool(__stdcall* WinUsb_ReadIsochPipeAsap)(_In_  WINUSB_ISOCH_BUFFER_HANDLE BufferHandle, _In_  ULONG Offset, _In_  ULONG Length, _In_  bool ContinueStream, _In_  ULONG NumberOfPackets, _Out_writes_(NumberOfPackets) PUSBD_ISO_PACKET_DESCRIPTOR IsoPacketDescriptors, _In_opt_ LPOVERLAPPED Overlapped);
//
//WinUsb_Initialize SK_WinUsb_Initialize;
//WinUsb_Free SK_WinUsb_Free;
//WinUsb_GetAssociatedInterface SK_WinUsb_GetAssociatedInterface;
//WinUsb_GetDescriptor SK_WinUsb_GetDescriptor;
//WinUsb_QueryInterfaceSettings SK_WinUsb_QueryInterfaceSettings;
//WinUsb_QueryDeviceInformation SK_WinUsb_QueryDeviceInformation;
//WinUsb_SetCurrentAlternateSetting SK_WinUsb_SetCurrentAlternateSetting;
//WinUsb_GetCurrentAlternateSetting SK_WinUsb_GetCurrentAlternateSetting;
//WinUsb_QueryPipe SK_WinUsb_QueryPipe;
//WinUsb_QueryPipeEx SK_WinUsb_QueryPipeEx;
//WinUsb_SetPipePolicy SK_WinUsb_SetPipePolicy;
//WinUsb_GetPipePolicy SK_WinUsb_GetPipePolicy;
//WinUsb_ReadPipe SK_WinUsb_ReadPipe;
//WinUsb_WritePipe SK_WinUsb_WritePipe;
//WinUsb_ControlTransfer SK_WinUsb_ControlTransfer;
//WinUsb_ResetPipe SK_WinUsb_ResetPipe;
//WinUsb_AbortPipe SK_WinUsb_AbortPipe;
//WinUsb_FlushPipe SK_WinUsb_FlushPipe;
//WinUsb_SetPowerPolicy SK_WinUsb_SetPowerPolicy;
//WinUsb_GetPowerPolicy SK_WinUsb_GetPowerPolicy;
//WinUsb_GetOverlappedResult SK_WinUsb_GetOverlappedResult;
//WinUsb_GetCurrentFrameNumber SK_WinUsb_GetCurrentFrameNumber;
//WinUsb_GetAdjustedFrameNumber SK_WinUsb_GetAdjustedFrameNumber;
//WinUsb_RegisterIsochBuffer SK_WinUsb_RegisterIsochBuffer;
//WinUsb_UnregisterIsochBuffer SK_WinUsb_UnregisterIsochBuffer;
//WinUsb_WriteIsochPipe SK_WinUsb_WriteIsochPipe;
//WinUsb_ReadIsochPipe SK_WinUsb_ReadIsochPipe;
//WinUsb_WriteIsochPipeAsap SK_WinUsb_WriteIsochPipeAsap;
//WinUsb_ReadIsochPipeAsap SK_WinUsb_ReadIsochPipeAsap;

const char* vanityBool(bool i) {
    return i == 1 ? "True" : "False";
}

void initWinusb(seekThermalCamera* stc) {

	//HMODULE winusb = LoadLibraryA("winusb.dll");
 //   HMODULE setupapi = LoadLibraryA("setupapi.dll");

    //SK_WinUsb_Initialize = (WinUsb_Initialize)GetProcAddress(winusb, "WinUsb_Initialize");
    //SK_WinUsb_Free = (WinUsb_Free)GetProcAddress(winusb, "WinUsb_Free");
    //SK_WinUsb_GetAssociatedInterface = (WinUsb_GetAssociatedInterface)GetProcAddress(winusb, "WinUsb_GetAssociatedInterface");
    //SK_WinUsb_GetDescriptor = (WinUsb_GetDescriptor)GetProcAddress(winusb, "WinUsb_GetDescriptor");
    //SK_WinUsb_QueryInterfaceSettings = (WinUsb_QueryInterfaceSettings)GetProcAddress(winusb, "WinUsb_QueryInterfaceSettings");
    //SK_WinUsb_QueryDeviceInformation = (WinUsb_QueryDeviceInformation)GetProcAddress(winusb, "WinUsb_QueryDeviceInformation");
    //SK_WinUsb_SetCurrentAlternateSetting = (WinUsb_SetCurrentAlternateSetting)GetProcAddress(winusb, "WinUsb_SetCurrentAlternateSetting");
    //SK_WinUsb_QueryPipe = (WinUsb_QueryPipe)GetProcAddress(winusb, "WinUsb_QueryPipe");
    //SK_WinUsb_QueryPipeEx = (WinUsb_QueryPipeEx)GetProcAddress(winusb, "WinUsb_QueryPipeEx");
    //SK_WinUsb_SetPipePolicy = (WinUsb_SetPipePolicy)GetProcAddress(winusb, "WinUsb_SetPipePolicy");
    //SK_WinUsb_ReadPipe = (WinUsb_ReadPipe)GetProcAddress(winusb, "WinUsb_ReadPipe");
    //SK_WinUsb_WritePipe = (WinUsb_WritePipe)GetProcAddress(winusb, "WinUsb_WritePipe");
    //SK_WinUsb_ControlTransfer = (WinUsb_ControlTransfer)GetProcAddress(winusb, "WinUsb_ControlTransfer");
    //SK_WinUsb_ResetPipe = (WinUsb_ResetPipe)GetProcAddress(winusb, "WinUsb_ResetPipe");
    //SK_WinUsb_AbortPipe = (WinUsb_AbortPipe)GetProcAddress(winusb, "WinUsb_AbortPipe");
    //SK_WinUsb_FlushPipe = (WinUsb_FlushPipe)GetProcAddress(winusb, "WinUsb_FlushPipe");
    //SK_WinUsb_SetPowerPolicy = (WinUsb_SetPowerPolicy)GetProcAddress(winusb, "WinUsb_SetPowerPolicy");
    //SK_WinUsb_GetPowerPolicy = (WinUsb_GetPowerPolicy)GetProcAddress(winusb, "WinUsb_GetPowerPolicy");
    //SK_WinUsb_GetOverlappedResult = (WinUsb_GetOverlappedResult)GetProcAddress(winusb, "WinUsb_GetOverlappedResult");
    //SK_WinUsb_GetCurrentFrameNumber = (WinUsb_GetCurrentFrameNumber)GetProcAddress(winusb, "WinUsb_GetCurrentFrameNumber");
    //SK_WinUsb_GetAdjustedFrameNumber = (WinUsb_GetAdjustedFrameNumber)GetProcAddress(winusb, "WinUsb_GetAdjustedFrameNumber");
    //SK_WinUsb_RegisterIsochBuffer = (WinUsb_RegisterIsochBuffer)GetProcAddress(winusb, "WinUsb_RegisterIsochBuffer");
    //SK_WinUsb_UnregisterIsochBuffer = (WinUsb_UnregisterIsochBuffer)GetProcAddress(winusb, "WinUsb_UnregisterIsochBuffer");
    //SK_WinUsb_WriteIsochPipe = (WinUsb_WriteIsochPipe)GetProcAddress(winusb, "WinUsb_WriteIsochPipe");
    //SK_WinUsb_ReadIsochPipe = (WinUsb_ReadIsochPipe)GetProcAddress(winusb, "WinUsb_ReadIsochPipe");
    //SK_WinUsb_WriteIsochPipeAsap = (WinUsb_WriteIsochPipeAsap)GetProcAddress(winusb, "WinUsb_WriteIsochPipeAsap");
    //SK_WinUsb_ReadIsochPipeAsap = (WinUsb_ReadIsochPipeAsap)GetProcAddress(winusb, "WinUsb_ReadIsochPipeAsap");

    //std::cout << "SK_WinUsb_Initialize: " << std::hex << SK_WinUsb_Initialize << std::endl;
    //std::cout << "SK_WinUsb_Free: " << std::hex << SK_WinUsb_Free << std::endl;
    //std::cout << "SK_WinUsb_GetAssociatedInterface: " << std::hex << SK_WinUsb_GetAssociatedInterface << std::endl;
    //std::cout << "SK_WinUsb_GetDescriptor: " << std::hex << SK_WinUsb_GetDescriptor << std::endl;
    //std::cout << "SK_WinUsb_QueryInterfaceSettings: " << std::hex << SK_WinUsb_QueryInterfaceSettings << std::endl;
    //std::cout << "SK_WinUsb_QueryDeviceInformation: " << std::hex << SK_WinUsb_QueryDeviceInformation << std::endl;
    //std::cout << "SK_WinUsb_SetCurrentAlternateSetting: " << std::hex << SK_WinUsb_SetCurrentAlternateSetting << std::endl;
    //std::cout << "SK_WinUsb_QueryPipe: " << std::hex << SK_WinUsb_QueryPipe << std::endl;
    //std::cout << "SK_WinUsb_QueryPipeEx: " << std::hex << SK_WinUsb_QueryPipeEx << std::endl;
    //std::cout << "SK_WinUsb_SetPipePolicy: " << std::hex << SK_WinUsb_SetPipePolicy << std::endl;
    //std::cout << "SK_WinUsb_ReadPipe: " << std::hex << SK_WinUsb_ReadPipe << std::endl;
    //std::cout << "SK_WinUsb_WritePipe: " << std::hex << SK_WinUsb_WritePipe << std::endl;
    //std::cout << "SK_WinUsb_ControlTransfer: " << std::hex << SK_WinUsb_ControlTransfer << std::endl;
    //std::cout << "SK_WinUsb_ResetPipe: " << std::hex << SK_WinUsb_ResetPipe << std::endl;
    //std::cout << "SK_WinUsb_AbortPipe: " << std::hex << SK_WinUsb_AbortPipe << std::endl;
    //std::cout << "SK_WinUsb_FlushPipe: " << std::hex << SK_WinUsb_FlushPipe << std::endl;
    //std::cout << "SK_WinUsb_SetPowerPolicy: " << std::hex << SK_WinUsb_SetPowerPolicy << std::endl;
    //std::cout << "SK_WinUsb_GetOverlappedResult: " << std::hex << SK_WinUsb_GetOverlappedResult << std::endl;
    //std::cout << "SK_WinUsb_GetCurrentFrameNumber: " << std::hex << SK_WinUsb_GetCurrentFrameNumber << std::endl;
    //std::cout << "SK_WinUsb_GetAdjustedFrameNumber: " << std::hex << SK_WinUsb_GetAdjustedFrameNumber << std::endl;
    //std::cout << "SK_WinUsb_RegisterIsochBuffer: " << std::hex << SK_WinUsb_RegisterIsochBuffer << std::endl;
    //std::cout << "SK_WinUsb_UnregisterIsochBuffer: " << std::hex << SK_WinUsb_UnregisterIsochBuffer << std::endl;
    //std::cout << "SK_WinUsb_WriteIsochPipe: " << std::hex << SK_WinUsb_WriteIsochPipe << std::endl;
    //std::cout << "SK_WinUsb_ReadIsochPipe: " << std::hex << SK_WinUsb_ReadIsochPipe << std::endl;
    //std::cout << "SK_WinUsb_WriteIsochPipeAsap: " << std::hex << SK_WinUsb_WriteIsochPipeAsap << std::endl;
    //std::cout << "SK_WinUsb_ReadIsochPipeAsap: " << std::hex << SK_WinUsb_ReadIsochPipeAsap << std::endl;

    if (connectSeek(stc)) {
        stc->initialise();
        stc->printCamInfo();
    }
}

void printGuid(GUID guid) {
    printf("Guid = {%08lX-%04hX-%04hX-%02hhX%02hhX-%02hhX%02hhX%02hhX%02hhX%02hhX%02hhX}\n",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
}

void Patch(BYTE* dst, BYTE* src, unsigned int size)
{
    DWORD oldprotect;
    VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
    memcpy(dst, src, size);
    VirtualProtect(dst, size, oldprotect, &oldprotect);
}

std::string ToNarrow(const wchar_t* s, char dfault = '?', const std::locale& loc = std::locale()){
    std::ostringstream stm;
    while (*s != L'\0') {  stm << std::use_facet< std::ctype<wchar_t> >(loc).narrow(*s++, dfault); }
    return stm.str();
}

GUID StringToGuid(const std::string& str)
{
    GUID guid;
    sscanf_s(str.c_str(),
        "{%8x-%4hx-%4hx-%2hhx%2hhx-%2hhx%2hhx%2hhx%2hhx%2hhx%2hhx}",
        &guid.Data1, &guid.Data2, &guid.Data3,
        &guid.Data4[0], &guid.Data4[1], &guid.Data4[2], &guid.Data4[3],
        &guid.Data4[4], &guid.Data4[5], &guid.Data4[6], &guid.Data4[7]);

    return guid;
}

std::string GuidToString(GUID guid)
{
    char guid_cstr[39];
    snprintf(guid_cstr, sizeof(guid_cstr),
        "{%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x}",
        guid.Data1, guid.Data2, guid.Data3,
        guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
        guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

    return std::string(guid_cstr);
}

//i dont know what this is or how i made it
//kill me please
bool connectSeek(seekThermalCamera* destination) {
    HDEVINFO devInfo = SetupDiGetClassDevsW(nullptr, nullptr, nullptr, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    HDEVINFO devInfo_adv = nullptr;
    SP_DEVINFO_DATA devInfoData{};
    _SP_DEVICE_INTERFACE_DATA devInterfaceData{};
    USES_CONVERSION;

    //couldnt have done this thing without SeekOFix, so thanks guys 
    for (int di = 0; ; di++) {
        bool success = false;
        devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
        success = SetupDiEnumDeviceInfo(devInfo, di, &devInfoData); //get current device
        if (!success) { break; } //reached end of devices or something went fucky-wucky
        HKEY hKey = SetupDiOpenDevRegKey(devInfo, &devInfoData, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_READ); //get reg key for the current device
        DWORD outL = 0;
        long output = RegGetValueW(hKey, nullptr, L"DeviceInterfaceGUIDs", RRF_RT_REG_SZ | RRF_RT_REG_MULTI_SZ, nullptr, nullptr, &outL); //get size of registry value of GUID
        if (outL != 0) {
            wchar_t* guid = new wchar_t[outL * 2]; //create wchar_t buffer for GUID
            output = RegGetValueW(hKey, nullptr, L"DeviceInterfaceGUIDs", RRF_RT_REG_SZ | RRF_RT_REG_MULTI_SZ, nullptr, guid, &outL); //write GUID to buffer
            std::string output = ToNarrow(guid); //convert it to std::string because the standard library is friendly
            GUID convertedGuid = StringToGuid(output); //make it a GUID
            
            devInfo_adv = SetupDiGetClassDevsW(&convertedGuid, NULL, nullptr, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT); //get the other kind of GUID we need for some reason
            SP_DEVICE_INTERFACE_DATA interfaceData{}; 
            interfaceData.cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

            DEVICE_DATA finalDD; //final cool stuff goes here
            for (int inf = 0; ; inf++) { //iterate over all interfaces on current device
                success = SetupDiEnumDeviceInterfaces(devInfo_adv, nullptr, &convertedGuid, inf, &interfaceData); //get current interface
                if (success) {
                    std::cout << "Interface: " << inf << std::endl;
                    SetupDiGetDeviceInterfaceDetailW(devInfo, &interfaceData, nullptr, 0, &outL, nullptr); //get data about interface
                    RetrieveDevicePath(convertedGuid, (&finalDD)->DevicePath, sizeof((&finalDD)->DevicePath), nullptr); //get path
                    std::string comp = ToNarrow(finalDD.DevicePath); //std::string is easy peasy
                    if ((comp.find("0010") != std::string::npos) && (comp.find("289d") != std::string::npos)) {
                        //seek device has been found
                        std::cout << "found seek" << std::endl;
                        finalDD.DeviceHandle = CreateFile(finalDD.DevicePath, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED, NULL); //get file handle
                        if (WinUsb_Initialize(finalDD.DeviceHandle, &(finalDD.WinusbHandle))) { //init using the sdk i made above
                            destination->dd = finalDD;
                            return true;
                        }
                    }
                }
                else {
                    break;
                }
            }   
        }
    }
    return false;
}

bool WUSB_SendData(WINUSB_INTERFACE_HANDLE hndl, uint16_t rType, uint16_t req, uint16_t val, uint16_t ind, byte* data, uint16_t dLen) {
    WINUSB_SETUP_PACKET wsp;
    wsp.RequestType = rType | 0x00;
    wsp.Request = req;
    wsp.Value = val;
    wsp.Index = ind;
    wsp.Length = dLen;
    ULONG sentData = 0;
    return WinUsb_ControlTransfer(hndl, wsp, (PUCHAR)data, dLen, &sentData, 0);
}

bool WUSB_GetData(WINUSB_INTERFACE_HANDLE hndl, uint16_t rType, uint16_t req, uint16_t val, uint16_t ind, byte* data, uint16_t dLen) {
    WINUSB_SETUP_PACKET wsp;
    wsp.RequestType = rType | 0x80;
    wsp.Request = req;
    wsp.Value = val;
    wsp.Index = ind;
    wsp.Length = dLen;
    ULONG sentData = 0;
    return WinUsb_ControlTransfer(hndl, wsp, (PUCHAR)data, dLen, &sentData, 0);
}

std::string arConvert(byte* inArr, int length) {
    std::ostringstream oss;
    for (int i = 0; i < length; i++) {
        oss << std::hex << *(char*)(inArr + i);
    }
    return oss.str();
}

void seekThermalCamera::initialise()
{
    byte s1d[1] = { 0x01 };
    bool s1 = WUSB_SendData(this->dd.WinusbHandle, 0x41, 0x54, 0, 0, s1d, 1);
    if (!s1) { std::cout << "init failed: " << GetLastError() << std::endl; }

    byte s2d[2] = { 0x00, 0x00 };
    bool s2 = WUSB_SendData(this->dd.WinusbHandle, 0x41, 0x3c, 0, 0, s2d, 2);
    if (!s2) { std::cout << "init failed: " << GetLastError() << std::endl; }

    byte s3d[6] = { 0x20, 0x00, 0x30, 0x00, 0x00, 0x00 };
    bool s3 = WUSB_SendData(this->dd.WinusbHandle, 0x41, 0x56, 0, 0, s3d, 6);
    if (!s3) { std::cout << "init failed: " << GetLastError() << std::endl; }

    byte s4d[6] = { 0x20, 0x00, 0x50, 0x00, 0x00, 0x00 };
    bool s4 = WUSB_SendData(this->dd.WinusbHandle, 0x41, 0x56, 0, 0, s4d, 6);
    if (!s4) { std::cout << "init failed: " << GetLastError() << std::endl; }

    byte s5d[6] = { 0x0c, 0x00, 0x70, 0x00, 0x00, 0x00 };
    bool s5 = WUSB_SendData(this->dd.WinusbHandle, 0x41, 0x56, 0, 0, s5d, 6);
    if (!s5) { std::cout << "init failed: " << GetLastError() << std::endl; }

    byte s6d[6] = { 0x06, 0x00, 0x08, 0x00, 0x00, 0x00 };
    bool s6 = WUSB_SendData(this->dd.WinusbHandle, 0x41, 0x56, 0, 0, s6d, 6);
    if (!s6) { std::cout << "init failed: " << GetLastError() << std::endl; }

    byte s7d[2] = { 0x08, 0x00 };
    bool s7 = WUSB_SendData(this->dd.WinusbHandle, 0x41, 0x3e, 0, 0, s7d, 2);
    if (!s7) { std::cout << "init failed: " << GetLastError() << std::endl; }

    byte s8d[2] = { 0x01, 0x00 };
    bool s8 = WUSB_SendData(this->dd.WinusbHandle, 0x41, 0x3c, 0, 0, s8d, 2);
    if (!s8) { std::cout << "init failed: " << GetLastError() << std::endl; }
}

void seekThermalCamera::printCamInfo()
{
    byte fwInfo[64]{};
    if (WUSB_GetData(this->dd.WinusbHandle, 0xc1, 0x4e, 0, 0, (byte*)fwInfo, 64)) {
        std::cout << arConvert(fwInfo, 64) << std::endl;
    }
}

bool seekThermalCamera::getFrame(rawThermalFrameContainer* empty)
{
    //frame = 64896
    byte reqFrame[4] = { 0xc0, 0x7e, 0x00, 0x00 };
    WUSB_SendData(this->dd.WinusbHandle, 0x41, 0x53, 0, 0, reqFrame, 4);
    ULONG tranny = 0;
    WinUsb_ReadPipe(this->dd.WinusbHandle, 0x81, (byte*)&empty->data, 16224, &tranny, nullptr);
    WinUsb_ReadPipe(this->dd.WinusbHandle, 0x81, (byte*)&empty->data + 16224, 16224, &tranny, nullptr);
    WinUsb_ReadPipe(this->dd.WinusbHandle, 0x81, (byte*)&empty->data + 32448, 16224, &tranny, nullptr);
    WinUsb_ReadPipe(this->dd.WinusbHandle, 0x81, (byte*)&empty->data + 48672, 16224, &tranny, nullptr);

    UINT16 frame_min = 12000;
    UINT16 frame_max = 1000;

    std::fstream file_out;
    file_out.open("dump.dat", std::ios_base::out);
    file_out.write((char*)&empty->data, sizeof(empty->data));
    file_out.close();

    int uLongPT = 0;
    int goodPx = 0;
    int badPx = 0;
    empty->frameType = empty->data[20];

    //convert data to uInt16;
    for (int i = 0; i < 32448; i++) {
        UINT16 cur = ((uint16_t)(empty->data[uLongPT])) | (uint16_t)empty->data[uLongPT + 1] << 8;
        empty->convertedData[i] = cur;

        if ((int)cur > 12000 || (int)cur < 1000) {
            badPx++;
        }
        else {
            goodPx++;
        }

        uLongPT += 2;
    }

    //std::cout << "good: " << std::to_string(goodPx) << " bad: " << std::to_string(badPx) << std::endl;

    return true;
}
