#include <wtypes.h>
#include <iostream>
#include "setupapi.h"
#include <tchar.h>
#include "seekhandler.h"

typedef PVOID WINUSB_INTERFACE_HANDLE, * PWINUSB_INTERFACE_HANDLE;
typedef PVOID WINUSB_ISOCH_BUFFER_HANDLE, * PWINUSB_ISOCH_BUFFER_HANDLE;

typedef struct _USB_INTERFACE_DESCRIPTOR {
    UCHAR   bLength;
    UCHAR   bDescriptorType;
    UCHAR   bInterfaceNumber;
    UCHAR   bAlternateSetting;
    UCHAR   bNumEndpoints;
    UCHAR   bInterfaceClass;
    UCHAR   bInterfaceSubClass;
    UCHAR   bInterfaceProtocol;
    UCHAR   iInterface;
} USB_INTERFACE_DESCRIPTOR, * PUSB_INTERFACE_DESCRIPTOR;

typedef struct _WINUSB_SETUP_PACKET {
    UCHAR   RequestType;
    UCHAR   Request;
    USHORT  Value;
    USHORT  Index;
    USHORT  Length;
} WINUSB_SETUP_PACKET, * PWINUSB_SETUP_PACKET;

typedef enum _USBD_PIPE_TYPE {
    UsbdPipeTypeControl,
    UsbdPipeTypeIsochronous,
    UsbdPipeTypeBulk,
    UsbdPipeTypeInterrupt
} USBD_PIPE_TYPE;

typedef struct _WINUSB_PIPE_INFORMATION {
    USBD_PIPE_TYPE  PipeType;
    UCHAR           PipeId;
    USHORT          MaximumPacketSize;
    UCHAR           Interval;
} WINUSB_PIPE_INFORMATION, * PWINUSB_PIPE_INFORMATION;

typedef struct _WINUSB_PIPE_INFORMATION_EX {
    USBD_PIPE_TYPE PipeType;
    UCHAR          PipeId;
    USHORT         MaximumPacketSize;
    UCHAR          Interval;
    ULONG          MaximumBytesPerInterval;
} WINUSB_PIPE_INFORMATION_EX, * PWINUSB_PIPE_INFORMATION_EX;

typedef LONG USBD_STATUS;

typedef struct _USBD_ISO_PACKET_DESCRIPTOR {
    ULONG Offset;
    ULONG Length;
    USBD_STATUS Status;
} USBD_ISO_PACKET_DESCRIPTOR, * PUSBD_ISO_PACKET_DESCRIPTOR;

typedef bool(__stdcall* WinUsb_Initialize)(_In_  HANDLE DeviceHandle, _Out_ PWINUSB_INTERFACE_HANDLE InterfaceHandle);
typedef bool(__stdcall* WinUsb_Free)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle);
typedef bool(__stdcall* WinUsb_GetAssociatedInterface)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR AssociatedInterfaceIndex, _Out_ PWINUSB_INTERFACE_HANDLE AssociatedInterfaceHandle);
typedef bool(__stdcall* WinUsb_GetDescriptor)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR DescriptorType, _In_  UCHAR Index, _In_  USHORT LanguageID, _Out_writes_bytes_to_opt_(BufferLength, *LengthTransferred) PUCHAR Buffer, _In_  ULONG BufferLength, _Out_ PULONG LengthTransferred);
typedef bool(__stdcall* WinUsb_QueryInterfaceSettings)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR AlternateInterfaceNumber, _Out_ PUSB_INTERFACE_DESCRIPTOR UsbAltInterfaceDescriptor);
typedef bool(__stdcall* WinUsb_QueryDeviceInformation)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  ULONG InformationType, _Inout_ PULONG BufferLength, _Out_writes_bytes_(*BufferLength) PVOID Buffer);
typedef bool(__stdcall* WinUsb_SetCurrentAlternateSetting)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR SettingNumber);
typedef bool(__stdcall* WinUsb_GetCurrentAlternateSetting)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _Out_ PUCHAR SettingNumber);
typedef bool(__stdcall* WinUsb_QueryPipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR AlternateInterfaceNumber, _In_  UCHAR PipeIndex, _Out_ PWINUSB_PIPE_INFORMATION PipeInformation);
typedef bool(__stdcall* WinUsb_QueryPipeEx)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR AlternateSettingNumber, _In_  UCHAR PipeIndex, _Out_ PWINUSB_PIPE_INFORMATION_EX PipeInformationEx);
typedef bool(__stdcall* WinUsb_SetPipePolicy)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID, _In_  ULONG PolicyType, _In_  ULONG ValueLength, _In_reads_bytes_(ValueLength) PVOID Value);
typedef bool(__stdcall* WinUsb_GetPipePolicy)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID, _In_  ULONG PolicyType, _Inout_ PULONG ValueLength, _Out_writes_bytes_(*ValueLength) PVOID Value);
typedef bool(__stdcall* WinUsb_ReadPipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID, _Out_writes_bytes_to_opt_(BufferLength, *LengthTransferred) PUCHAR Buffer, _In_  ULONG BufferLength, _Out_opt_ PULONG LengthTransferred, _In_opt_ LPOVERLAPPED Overlapped);
typedef bool(__stdcall* WinUsb_WritePipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID, _In_reads_bytes_(BufferLength) PUCHAR Buffer, _In_  ULONG BufferLength, _Out_opt_ PULONG LengthTransferred, _In_opt_ LPOVERLAPPED Overlapped);
typedef bool(__stdcall* WinUsb_ControlTransfer)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  WINUSB_SETUP_PACKET SetupPacket, _Out_writes_bytes_to_opt_(BufferLength, *LengthTransferred) PUCHAR Buffer, _In_  ULONG BufferLength, _Out_opt_ PULONG LengthTransferred, _In_opt_  LPOVERLAPPED Overlapped);
typedef bool(__stdcall* WinUsb_ResetPipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID);
typedef bool(__stdcall* WinUsb_AbortPipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID);
typedef bool(__stdcall* WinUsb_FlushPipe)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID);
typedef bool(__stdcall* WinUsb_SetPowerPolicy)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  ULONG PolicyType, _In_  ULONG ValueLength, _In_reads_bytes_(ValueLength) PVOID Value);
typedef bool(__stdcall* WinUsb_GetPowerPolicy)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  ULONG PolicyType, _Inout_ PULONG ValueLength, _Out_writes_bytes_(*ValueLength) PVOID Value);
typedef bool(__stdcall* WinUsb_GetOverlappedResult)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  LPOVERLAPPED lpOverlapped, _Out_ LPDWORD lpNumberOfBytesTransferred, _In_ bool bWait);
typedef bool(__stdcall* WinUsb_GetCurrentFrameNumber)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _Out_ PULONG CurrentFrameNumber, _Out_ LARGE_INTEGER* TimeStamp);
typedef bool(__stdcall* WinUsb_GetAdjustedFrameNumber)(_Inout_ PULONG CurrentFrameNumber, _In_  LARGE_INTEGER TimeStamp);
typedef bool(__stdcall* WinUsb_RegisterIsochBuffer)(_In_  WINUSB_INTERFACE_HANDLE InterfaceHandle, _In_  UCHAR PipeID, _Inout_updates_bytes_(BufferLength) PUCHAR Buffer, _In_  ULONG BufferLength, _Out_ PWINUSB_ISOCH_BUFFER_HANDLE IsochBufferHandle);
typedef bool(__stdcall* WinUsb_UnregisterIsochBuffer)(_In_  WINUSB_ISOCH_BUFFER_HANDLE IsochBufferHandle);
typedef bool(__stdcall* WinUsb_WriteIsochPipe)(_In_  WINUSB_ISOCH_BUFFER_HANDLE BufferHandle, _In_  ULONG Offset, _In_  ULONG Length, _Inout_ PULONG FrameNumber, _In_opt_ LPOVERLAPPED Overlapped);
typedef bool(__stdcall* WinUsb_ReadIsochPipe)(_In_  WINUSB_ISOCH_BUFFER_HANDLE BufferHandle, _In_  ULONG Offset, _In_  ULONG Length, _Inout_ PULONG FrameNumber, _In_  ULONG NumberOfPackets, _Out_writes_(NumberOfPackets) PUSBD_ISO_PACKET_DESCRIPTOR IsoPacketDescriptors, _In_opt_ LPOVERLAPPED Overlapped);
typedef bool(__stdcall* WinUsb_WriteIsochPipeAsap)(_In_  WINUSB_ISOCH_BUFFER_HANDLE BufferHandle, _In_  ULONG Offset, _In_  ULONG Length, _In_  bool ContinueStream, _In_opt_ LPOVERLAPPED Overlapped);
typedef bool(__stdcall* WinUsb_ReadIsochPipeAsap)(_In_  WINUSB_ISOCH_BUFFER_HANDLE BufferHandle, _In_  ULONG Offset, _In_  ULONG Length, _In_  bool ContinueStream, _In_  ULONG NumberOfPackets, _Out_writes_(NumberOfPackets) PUSBD_ISO_PACKET_DESCRIPTOR IsoPacketDescriptors, _In_opt_ LPOVERLAPPED Overlapped);

WinUsb_Initialize SK_WinUsb_Initialize;
WinUsb_Free SK_WinUsb_Free;
WinUsb_GetAssociatedInterface SK_WinUsb_GetAssociatedInterface;
WinUsb_GetDescriptor SK_WinUsb_GetDescriptor;
WinUsb_QueryInterfaceSettings SK_WinUsb_QueryInterfaceSettings;
WinUsb_QueryDeviceInformation SK_WinUsb_QueryDeviceInformation;
WinUsb_SetCurrentAlternateSetting SK_WinUsb_SetCurrentAlternateSetting;
WinUsb_GetCurrentAlternateSetting SK_WinUsb_GetCurrentAlternateSetting;
WinUsb_QueryPipe SK_WinUsb_QueryPipe;
WinUsb_QueryPipeEx SK_WinUsb_QueryPipeEx;
WinUsb_SetPipePolicy SK_WinUsb_SetPipePolicy;
WinUsb_GetPipePolicy SK_WinUsb_GetPipePolicy;
WinUsb_ReadPipe SK_WinUsb_ReadPipe;
WinUsb_WritePipe SK_WinUsb_WritePipe;
WinUsb_ControlTransfer SK_WinUsb_ControlTransfer;
WinUsb_ResetPipe SK_WinUsb_ResetPipe;
WinUsb_AbortPipe SK_WinUsb_AbortPipe;
WinUsb_FlushPipe SK_WinUsb_FlushPipe;
WinUsb_SetPowerPolicy SK_WinUsb_SetPowerPolicy;
WinUsb_GetPowerPolicy SK_WinUsb_GetPowerPolicy;
WinUsb_GetOverlappedResult SK_WinUsb_GetOverlappedResult;
WinUsb_GetCurrentFrameNumber SK_WinUsb_GetCurrentFrameNumber;
WinUsb_GetAdjustedFrameNumber SK_WinUsb_GetAdjustedFrameNumber;
WinUsb_RegisterIsochBuffer SK_WinUsb_RegisterIsochBuffer;
WinUsb_UnregisterIsochBuffer SK_WinUsb_UnregisterIsochBuffer;
WinUsb_WriteIsochPipe SK_WinUsb_WriteIsochPipe;
WinUsb_ReadIsochPipe SK_WinUsb_ReadIsochPipe;
WinUsb_WriteIsochPipeAsap SK_WinUsb_WriteIsochPipeAsap;
WinUsb_ReadIsochPipeAsap SK_WinUsb_ReadIsochPipeAsap;

const char* vanityBool(bool i) {
    return i == 1 ? "True" : "False";
}

void initWinusb() {

	HMODULE winusb = LoadLibraryA("winusb.dll");
    HMODULE setupapi = LoadLibraryA("setupapi.dll");

    SK_WinUsb_Initialize = (WinUsb_Initialize)GetProcAddress(winusb, "WinUsb_Initialize");
    SK_WinUsb_Free = (WinUsb_Free)GetProcAddress(winusb, "WinUsb_Free");
    SK_WinUsb_GetAssociatedInterface = (WinUsb_GetAssociatedInterface)GetProcAddress(winusb, "WinUsb_GetAssociatedInterface");
    SK_WinUsb_GetDescriptor = (WinUsb_GetDescriptor)GetProcAddress(winusb, "WinUsb_GetDescriptor");
    SK_WinUsb_QueryInterfaceSettings = (WinUsb_QueryInterfaceSettings)GetProcAddress(winusb, "WinUsb_QueryInterfaceSettings");
    SK_WinUsb_QueryDeviceInformation = (WinUsb_QueryDeviceInformation)GetProcAddress(winusb, "WinUsb_QueryDeviceInformation");
    SK_WinUsb_SetCurrentAlternateSetting = (WinUsb_SetCurrentAlternateSetting)GetProcAddress(winusb, "WinUsb_SetCurrentAlternateSetting");
    SK_WinUsb_QueryPipe = (WinUsb_QueryPipe)GetProcAddress(winusb, "WinUsb_QueryPipe");
    SK_WinUsb_QueryPipeEx = (WinUsb_QueryPipeEx)GetProcAddress(winusb, "WinUsb_QueryPipeEx");
    SK_WinUsb_SetPipePolicy = (WinUsb_SetPipePolicy)GetProcAddress(winusb, "WinUsb_SetPipePolicy");
    SK_WinUsb_ReadPipe = (WinUsb_ReadPipe)GetProcAddress(winusb, "WinUsb_ReadPipe");
    SK_WinUsb_WritePipe = (WinUsb_WritePipe)GetProcAddress(winusb, "WinUsb_WritePipe");
    SK_WinUsb_ControlTransfer = (WinUsb_ControlTransfer)GetProcAddress(winusb, "WinUsb_ControlTransfer");
    SK_WinUsb_ResetPipe = (WinUsb_ResetPipe)GetProcAddress(winusb, "WinUsb_ResetPipe");
    SK_WinUsb_AbortPipe = (WinUsb_AbortPipe)GetProcAddress(winusb, "WinUsb_AbortPipe");
    SK_WinUsb_FlushPipe = (WinUsb_FlushPipe)GetProcAddress(winusb, "WinUsb_FlushPipe");
    SK_WinUsb_SetPowerPolicy = (WinUsb_SetPowerPolicy)GetProcAddress(winusb, "WinUsb_SetPowerPolicy");
    SK_WinUsb_GetPowerPolicy = (WinUsb_GetPowerPolicy)GetProcAddress(winusb, "WinUsb_GetPowerPolicy");
    SK_WinUsb_GetOverlappedResult = (WinUsb_GetOverlappedResult)GetProcAddress(winusb, "WinUsb_GetOverlappedResult");
    SK_WinUsb_GetCurrentFrameNumber = (WinUsb_GetCurrentFrameNumber)GetProcAddress(winusb, "WinUsb_GetCurrentFrameNumber");
    SK_WinUsb_GetAdjustedFrameNumber = (WinUsb_GetAdjustedFrameNumber)GetProcAddress(winusb, "WinUsb_GetAdjustedFrameNumber");
    SK_WinUsb_RegisterIsochBuffer = (WinUsb_RegisterIsochBuffer)GetProcAddress(winusb, "WinUsb_RegisterIsochBuffer");
    SK_WinUsb_UnregisterIsochBuffer = (WinUsb_UnregisterIsochBuffer)GetProcAddress(winusb, "WinUsb_UnregisterIsochBuffer");
    SK_WinUsb_WriteIsochPipe = (WinUsb_WriteIsochPipe)GetProcAddress(winusb, "WinUsb_WriteIsochPipe");
    SK_WinUsb_ReadIsochPipe = (WinUsb_ReadIsochPipe)GetProcAddress(winusb, "WinUsb_ReadIsochPipe");
    SK_WinUsb_WriteIsochPipeAsap = (WinUsb_WriteIsochPipeAsap)GetProcAddress(winusb, "WinUsb_WriteIsochPipeAsap");
    SK_WinUsb_ReadIsochPipeAsap = (WinUsb_ReadIsochPipeAsap)GetProcAddress(winusb, "WinUsb_ReadIsochPipeAsap");

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

    std::cout << vanityBool(isSeekConnected()) << std::endl;
}

bool isSeekConnected() {
    unsigned index;
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA DeviceInfoData;
    TCHAR HardwareID[1024];

    // List all connected USB devices
    hDevInfo = SetupDiGetClassDevs(NULL, TEXT("USB"), NULL, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    for (index = 0; ; index++) {
        DeviceInfoData.cbSize = sizeof(DeviceInfoData);
        if (!SetupDiEnumDeviceInfo(hDevInfo, index, &DeviceInfoData)) {
            return false;     // no match
        }

        SetupDiGetDeviceRegistryProperty(hDevInfo, &DeviceInfoData, SPDRP_HARDWAREID, NULL, (BYTE*)HardwareID, sizeof(HardwareID), NULL);

        if (_tcsstr(HardwareID, _T("VID_289D&PID_0010"))) {
            return true;     // match
        }
    }
}

