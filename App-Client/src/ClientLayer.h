#pragma once

#include "Walnut/Layer.h"
#include "Walnut/Networking/Client.h"

#include "Walnut/UI/Console.h"

#include "UserInfo.h"

#include <set>
#include <filesystem>

class ClientLayer : public Walnut::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(float ts) override;
	virtual void OnUIRender() override;

	bool IsConnected() const;
	void OnDisconnectButton();
private:
	// UI
	void UI_ConnectionModal();
	void UI_ClientList();

	// Server event callbacks
	void OnConnected();
	void OnDisconnected();
	void OnDataReceived(const Walnut::Buffer buffer);

	void SendChatMessage(std::string_view message);
	void SaveMessageHistoryToFile(const std::filesystem::path& filepath);
	bool LoadMessageHistoryFromFile(const std::filesystem::path& filepath);

private:
	void SaveConnectionDetails(const std::filesystem::path& filepath);
	bool LoadConnectionDetails(const std::filesystem::path& filepath);
private:
	std::unique_ptr<Walnut::Client> m_Client;
	Walnut::UI::Console m_Console{ "Chat" };
	std::string m_ServerIP;
	std::string m_DataDirectory = "Data";
	std::string m_MessageHistoryFileName = "MessageHistory.yaml";
	std::filesystem::path m_ConnectionDetailsFilePath = m_DataDirectory + "\\ConnectionDetails.yaml";

	Walnut::Buffer m_ScratchBuffer;

	float m_ColorBuffer[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	std::string m_Username = "";
	std::string m_DirectMessageUsername = "";
	bool m_SendDirectMessage = false;
	
	uint32_t m_Color = 0xffffffff;

	std::map<std::string, UserInfo> m_ConnectedClients;
	std::vector<ChatMessage> m_MessageHistory;
	std::filesystem::path m_MessageHistoryFilePath;
	bool m_ConnectionModalOpen = false;
	bool m_ShowSuccessfulConnectionMessage = false;
	
	// Send client list every ten seconds
	const float m_ClientListInterval = 10.0f;
	float m_ClientListTimer = m_ClientListInterval;
	
};