
#include "global_define.h"
#include "eq_stream_proxy.h"
#include "eq_stream.h"
#include "struct_strategy.h"


EQStreamProxy::EQStreamProxy(std::shared_ptr<EQStream> &stream, const StructStrategy *structs, OpcodeManager **opcodes)
:	m_stream(stream),
	m_structs(structs),
	m_opcodes(opcodes)
{
	_eqp
	stream = nullptr;	//take the stream.
	m_stream->SetOpcodeManager(m_opcodes);
}

EQStreamProxy::~EQStreamProxy() {
	_eqp
}

std::string EQStreamProxy::Describe() const {
	_eqp
	return(m_structs->Describe());
}

const ClientVersion EQStreamProxy::GetClientVersion() const
{
	_eqp
	return m_structs->GetClientVersion();
}

void EQStreamProxy::QueuePacket(const EQApplicationPacket *p, bool ack_req) {
	_eqp
	if(p == nullptr)
		return;

	EQApplicationPacket *newp = p->Copy();
	FastQueuePacket(&newp, ack_req);
}

void EQStreamProxy::FastQueuePacket(EQApplicationPacket **p, bool ack_req) {
	_eqp
	if(p == nullptr || *p == nullptr)
		return;
	m_structs->Encode(p, m_stream, ack_req);
}

EQApplicationPacket *EQStreamProxy::PopPacket() {
	_eqp
	EQApplicationPacket *pack = m_stream->PopPacket();
	if(pack == nullptr)
		return(nullptr);

	//pass this packet through the struct strategy.
	m_structs->Decode(pack);
	return(pack);
}

void EQStreamProxy::Close() {
	_eqp
	m_stream->Close();
}

uint32 EQStreamProxy::GetRemoteIP() const {
	_eqp
	return(m_stream->GetRemoteIP());
}

uint16 EQStreamProxy::GetRemotePort() const {
	_eqp
	return(m_stream->GetRemotePort());
}

const uint32 EQStreamProxy::GetBytesSent() const
{
	_eqp
	return(m_stream->GetBytesSent());
}

const uint32 EQStreamProxy::GetBytesRecieved() const
{
	_eqp
	return(m_stream->GetBytesRecieved());
}

const uint32 EQStreamProxy::GetBytesSentPerSecond() const
{
	_eqp
	return(m_stream->GetBytesSentPerSecond());
}

const uint32 EQStreamProxy::GetBytesRecvPerSecond() const
{
	_eqp
	return(m_stream->GetBytesRecvPerSecond());
}

void EQStreamProxy::ReleaseFromUse() {
	_eqp
	m_stream->ReleaseFromUse();
}

void EQStreamProxy::RemoveData() {
	_eqp
	m_stream->RemoveData();
}

bool EQStreamProxy::CheckState(EQStreamState state) {
	_eqp
	if(m_stream)
		return(m_stream->CheckState(state));

	return false;
}

