// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CommandData.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "CommandData.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace Data {
class CommandDataDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<CommandData> {
} _CommandData_default_instance_;

namespace protobuf_CommandData_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];

}  // namespace

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CommandData, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CommandData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CommandData, pid_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(CommandData, cmd_),
  0,
  1,
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 6, sizeof(CommandData)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_CommandData_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "CommandData.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

}  // namespace

void TableStruct::Shutdown() {
  _CommandData_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  ::Data::protobuf_Base_2eproto::InitDefaults();
  _CommandData_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\021CommandData.proto\022\004Data\032\nBase.proto\":\n"
      "\013CommandData\022\013\n\003pid\030\001 \002(\r\022\036\n\003cmd\030\002 \002(\0162\021"
      ".Data.CommandType"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 97);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "CommandData.proto", &protobuf_RegisterTypes);
  ::Data::protobuf_Base_2eproto::AddDescriptors();
  ::google::protobuf::internal::OnShutdown(&TableStruct::Shutdown);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;

}  // namespace protobuf_CommandData_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int CommandData::kPidFieldNumber;
const int CommandData::kCmdFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

CommandData::CommandData()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_CommandData_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:Data.CommandData)
}
CommandData::CommandData(const CommandData& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&pid_, &from.pid_,
    reinterpret_cast<char*>(&cmd_) -
    reinterpret_cast<char*>(&pid_) + sizeof(cmd_));
  // @@protoc_insertion_point(copy_constructor:Data.CommandData)
}

void CommandData::SharedCtor() {
  _cached_size_ = 0;
  ::memset(&pid_, 0, reinterpret_cast<char*>(&cmd_) -
    reinterpret_cast<char*>(&pid_) + sizeof(cmd_));
}

CommandData::~CommandData() {
  // @@protoc_insertion_point(destructor:Data.CommandData)
  SharedDtor();
}

void CommandData::SharedDtor() {
}

void CommandData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* CommandData::descriptor() {
  protobuf_CommandData_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_CommandData_2eproto::file_level_metadata[0].descriptor;
}

const CommandData& CommandData::default_instance() {
  protobuf_CommandData_2eproto::InitDefaults();
  return *internal_default_instance();
}

CommandData* CommandData::New(::google::protobuf::Arena* arena) const {
  CommandData* n = new CommandData;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void CommandData::Clear() {
// @@protoc_insertion_point(message_clear_start:Data.CommandData)
  if (_has_bits_[0 / 32] & 3u) {
    ::memset(&pid_, 0, reinterpret_cast<char*>(&cmd_) -
      reinterpret_cast<char*>(&pid_) + sizeof(cmd_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool CommandData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Data.CommandData)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 pid = 1;
      case 1: {
        if (tag == 8u) {
          set_has_pid();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &pid_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required .Data.CommandType cmd = 2;
      case 2: {
        if (tag == 16u) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::Data::CommandType_IsValid(value)) {
            set_cmd(static_cast< ::Data::CommandType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(2, value);
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:Data.CommandData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Data.CommandData)
  return false;
#undef DO_
}

void CommandData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Data.CommandData)
  // required uint32 pid = 1;
  if (has_pid()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->pid(), output);
  }

  // required .Data.CommandType cmd = 2;
  if (has_cmd()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      2, this->cmd(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Data.CommandData)
}

::google::protobuf::uint8* CommandData::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic;  // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Data.CommandData)
  // required uint32 pid = 1;
  if (has_pid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->pid(), target);
  }

  // required .Data.CommandType cmd = 2;
  if (has_cmd()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      2, this->cmd(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Data.CommandData)
  return target;
}

size_t CommandData::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:Data.CommandData)
  size_t total_size = 0;

  if (has_pid()) {
    // required uint32 pid = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->pid());
  }

  if (has_cmd()) {
    // required .Data.CommandType cmd = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->cmd());
  }

  return total_size;
}
size_t CommandData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Data.CommandData)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required uint32 pid = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->pid());

    // required .Data.CommandType cmd = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->cmd());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void CommandData::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Data.CommandData)
  GOOGLE_DCHECK_NE(&from, this);
  const CommandData* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const CommandData>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Data.CommandData)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Data.CommandData)
    MergeFrom(*source);
  }
}

void CommandData::MergeFrom(const CommandData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Data.CommandData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from._has_bits_[0 / 32] & 3u) {
    if (from.has_pid()) {
      set_pid(from.pid());
    }
    if (from.has_cmd()) {
      set_cmd(from.cmd());
    }
  }
}

void CommandData::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Data.CommandData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void CommandData::CopyFrom(const CommandData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Data.CommandData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool CommandData::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  return true;
}

void CommandData::Swap(CommandData* other) {
  if (other == this) return;
  InternalSwap(other);
}
void CommandData::InternalSwap(CommandData* other) {
  std::swap(pid_, other->pid_);
  std::swap(cmd_, other->cmd_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata CommandData::GetMetadata() const {
  protobuf_CommandData_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_CommandData_2eproto::file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// CommandData

// required uint32 pid = 1;
bool CommandData::has_pid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void CommandData::set_has_pid() {
  _has_bits_[0] |= 0x00000001u;
}
void CommandData::clear_has_pid() {
  _has_bits_[0] &= ~0x00000001u;
}
void CommandData::clear_pid() {
  pid_ = 0u;
  clear_has_pid();
}
::google::protobuf::uint32 CommandData::pid() const {
  // @@protoc_insertion_point(field_get:Data.CommandData.pid)
  return pid_;
}
void CommandData::set_pid(::google::protobuf::uint32 value) {
  set_has_pid();
  pid_ = value;
  // @@protoc_insertion_point(field_set:Data.CommandData.pid)
}

// required .Data.CommandType cmd = 2;
bool CommandData::has_cmd() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void CommandData::set_has_cmd() {
  _has_bits_[0] |= 0x00000002u;
}
void CommandData::clear_has_cmd() {
  _has_bits_[0] &= ~0x00000002u;
}
void CommandData::clear_cmd() {
  cmd_ = 0;
  clear_has_cmd();
}
::Data::CommandType CommandData::cmd() const {
  // @@protoc_insertion_point(field_get:Data.CommandData.cmd)
  return static_cast< ::Data::CommandType >(cmd_);
}
void CommandData::set_cmd(::Data::CommandType value) {
  assert(::Data::CommandType_IsValid(value));
  set_has_cmd();
  cmd_ = value;
  // @@protoc_insertion_point(field_set:Data.CommandData.cmd)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Data

// @@protoc_insertion_point(global_scope)
