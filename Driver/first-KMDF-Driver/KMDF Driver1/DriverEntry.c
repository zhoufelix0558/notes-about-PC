#include<ntifs.h>


VOID UnLoadDriver(PDRIVER_OBJECT pDriverObject)
{
	DbgPrint("UnLoadDriver success.");
}

NTSTATUS DriverEntry(PDRIVER_OBJECT pDriverObject, PUNICODE_STRING pRegistryPath)
{
	DbgPrint("%wZ",pRegistryPath);
	DbgPrint("LoadDriver success.");
	pDriverObject->DriverUnload = UnLoadDriver;
	return STATUS_SUCCESS;

}