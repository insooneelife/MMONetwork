// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SnakeCreateData.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "SnakeCreateData.pb.h"

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
class SnakeCreateDataDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<SnakeCreateData> {
} _SnakeCreateData_default_instance_;

namespace protobuf_SnakeCreateData_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];

}  // namespace

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SnakeCreateData, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SnakeCreateData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SnakeCreateData, entity_id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SnakeCreateData, body_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SnakeCreateData, control_type_),
  0,
  ~0u,
  1,
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 7, sizeof(SnakeCreateData)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_SnakeCreateData_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "SnakeCreateData.proto", schemas, file_default_instances, TableStruct::offsets, factory,
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
  _SnakeCreateData_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  ::Data::protobuf_Base_2eproto::InitDefaults();
  _SnakeCreateData_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\025SnakeCreateData.proto\022\004Data\032\nBase.prot"
      "o\"l\n\017SnakeCreateData\022\021\n\tentity_id\030\001 \002(\005\022"
      "\030\n\004body\030\002 \003(\0132\n.Data.Vec2\022,\n\014control_typ"
      "e\030\003 \001(\0162\021.Data.ControlType:\003NPC"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 151);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "SnakeCreateData.proto", &protobuf_RegisterTypes);
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

}  // namespace protobuf_SnakeCreateData_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int SnakeCreateData::kEntityIdFieldNumber;
const int SnakeCreateData::kBodyFieldNumber;
const int SnakeCreateData::kControlTypeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

SnakeCreateData::SnakeCreateData()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_SnakeCreateData_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:Data.SnakeCreateData)
}
SnakeCreateData::SnakeCreateData(const SnakeCreateData& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      body_(from.body_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&entity_id_, &from.entity_id_,
    reinterpret_cast<char*>(&control_type_) -
    reinterpret_cast<char*>(&entity_id_) + sizeof(control_type_));
  // @@protoc_insertion_point(copy_constructor:Data.SnakeCreateData)
}

void SnakeCreateData::SharedCtor() {
  _cached_size_ = 0;
  ::memset(&entity_id_, 0, reinterpret_cast<char*>(&control_type_) -
    reinterpret_cast<char*>(&entity_id_) + sizeof(control_type_));
}

SnakeCreateData::~SnakeCreateData() {
  // @@protoc_insertion_point(destructor:Data.SnakeCreateData)
  SharedDtor();
}

void SnakeCreateData::SharedDtor() {
}

void SnakeCreateData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SnakeCreateData::descriptor() {
  protobuf_SnakeCreateData_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_SnakeCreateData_2eproto::file_level_metadata[0].descriptor;
}

const SnakeCreateData& SnakeCreateData::default_instance() {
  protobuf_SnakeCreateData_2eproto::InitDefaults();
  return *internal_default_instance();
}

SnakeCreateData* SnakeCreateData::New(::google::protobuf::Arena* arena) const {
  SnakeCreateData* n = new SnakeCreateData;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void SnakeCreateData::Clear() {
// @@protoc_insertion_point(message_clear_start:Data.SnakeCreateData)
  body_.Clear();
  if (_has_bits_[0 / 32] & 3u) {
    ::memset(&entity_id_, 0, reinterpret_cast<char*>(&control_type_) -
      reinterpret_cast<char*>(&entity_id_) + sizeof(control_type_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool SnakeCreateData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Data.SnakeCreateData)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 entity_id = 1;
      case 1: {
        if (tag == 8u) {
          set_has_entity_id();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &entity_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // repeated .Data.Vec2 body = 2;
      case 2: {
        if (tag == 18u) {
          DO_(input->IncrementRecursionDepth());
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtualNoRecursionDepth(
                input, add_body()));
        } else {
          goto handle_unusual;
        }
        input->UnsafeDecrementRecursionDepth();
        break;
      }

      // optional .Data.ControlType control_type = 3 [default = NPC];
      case 3: {
        if (tag == 24u) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::Data::ControlType_IsValid(value)) {
            set_control_type(static_cast< ::Data::ControlType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(3, value);
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
  // @@protoc_insertion_point(parse_success:Data.SnakeCreateData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Data.SnakeCreateData)
  return false;
#undef DO_
}

void SnakeCreateData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Data.SnakeCreateData)
  // required int32 entity_id = 1;
  if (has_entity_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->entity_id(), output);
  }

  // repeated .Data.Vec2 body = 2;
  for (unsigned int i = 0, n = this->body_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->body(i), output);
  }

  // optional .Data.ControlType control_type = 3 [default = NPC];
  if (has_control_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      3, this->control_type(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Data.SnakeCreateData)
}

::google::protobuf::uint8* SnakeCreateData::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic;  // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Data.SnakeCreateData)
  // required int32 entity_id = 1;
  if (has_entity_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->entity_id(), target);
  }

  // repeated .Data.Vec2 body = 2;
  for (unsigned int i = 0, n = this->body_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        2, this->body(i), false, target);
  }

  // optional .Data.ControlType control_type = 3 [default = NPC];
  if (has_control_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      3, this->control_type(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Data.SnakeCreateData)
  return target;
}

size_t SnakeCreateData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Data.SnakeCreateData)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  // required int32 entity_id = 1;
  if (has_entity_id()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->entity_id());
  }
  // repeated .Data.Vec2 body = 2;
  {
    unsigned int count = this->body_size();
    total_size += 1UL * count;
    for (unsigned int i = 0; i < count; i++) {
      total_size +=
        ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
          this->body(i));
    }
  }

  // optional .Data.ControlType control_type = 3 [default = NPC];
  if (has_control_type()) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->control_type());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SnakeCreateData::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Data.SnakeCreateData)
  GOOGLE_DCHECK_NE(&from, this);
  const SnakeCreateData* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const SnakeCreateData>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Data.SnakeCreateData)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Data.SnakeCreateData)
    MergeFrom(*source);
  }
}

void SnakeCreateData::MergeFrom(const SnakeCreateData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Data.SnakeCreateData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  body_.MergeFrom(from.body_);
  if (from._has_bits_[0 / 32] & 3u) {
    if (from.has_entity_id()) {
      set_entity_id(from.entity_id());
    }
    if (from.has_control_type()) {
      set_control_type(from.control_type());
    }
  }
}

void SnakeCreateData::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Data.SnakeCreateData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SnakeCreateData::CopyFrom(const SnakeCreateData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Data.SnakeCreateData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SnakeCreateData::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000001) != 0x00000001) return false;
  if (!::google::protobuf::internal::AllAreInitialized(this->body())) return false;
  return true;
}

void SnakeCreateData::Swap(SnakeCreateData* other) {
  if (other == this) return;
  InternalSwap(other);
}
void SnakeCreateData::InternalSwap(SnakeCreateData* other) {
  body_.UnsafeArenaSwap(&other->body_);
  std::swap(entity_id_, other->entity_id_);
  std::swap(control_type_, other->control_type_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata SnakeCreateData::GetMetadata() const {
  protobuf_SnakeCreateData_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_SnakeCreateData_2eproto::file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// SnakeCreateData

// required int32 entity_id = 1;
bool SnakeCreateData::has_entity_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void SnakeCreateData::set_has_entity_id() {
  _has_bits_[0] |= 0x00000001u;
}
void SnakeCreateData::clear_has_entity_id() {
  _has_bits_[0] &= ~0x00000001u;
}
void SnakeCreateData::clear_entity_id() {
  entity_id_ = 0;
  clear_has_entity_id();
}
::google::protobuf::int32 SnakeCreateData::entity_id() const {
  // @@protoc_insertion_point(field_get:Data.SnakeCreateData.entity_id)
  return entity_id_;
}
void SnakeCreateData::set_entity_id(::google::protobuf::int32 value) {
  set_has_entity_id();
  entity_id_ = value;
  // @@protoc_insertion_point(field_set:Data.SnakeCreateData.entity_id)
}

// repeated .Data.Vec2 body = 2;
int SnakeCreateData::body_size() const {
  return body_.size();
}
void SnakeCreateData::clear_body() {
  body_.Clear();
}
const ::Data::Vec2& SnakeCreateData::body(int index) const {
  // @@protoc_insertion_point(field_get:Data.SnakeCreateData.body)
  return body_.Get(index);
}
::Data::Vec2* SnakeCreateData::mutable_body(int index) {
  // @@protoc_insertion_point(field_mutable:Data.SnakeCreateData.body)
  return body_.Mutable(index);
}
::Data::Vec2* SnakeCreateData::add_body() {
  // @@protoc_insertion_point(field_add:Data.SnakeCreateData.body)
  return body_.Add();
}
::google::protobuf::RepeatedPtrField< ::Data::Vec2 >*
SnakeCreateData::mutable_body() {
  // @@protoc_insertion_point(field_mutable_list:Data.SnakeCreateData.body)
  return &body_;
}
const ::google::protobuf::RepeatedPtrField< ::Data::Vec2 >&
SnakeCreateData::body() const {
  // @@protoc_insertion_point(field_list:Data.SnakeCreateData.body)
  return body_;
}

// optional .Data.ControlType control_type = 3 [default = NPC];
bool SnakeCreateData::has_control_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void SnakeCreateData::set_has_control_type() {
  _has_bits_[0] |= 0x00000002u;
}
void SnakeCreateData::clear_has_control_type() {
  _has_bits_[0] &= ~0x00000002u;
}
void SnakeCreateData::clear_control_type() {
  control_type_ = 0;
  clear_has_control_type();
}
::Data::ControlType SnakeCreateData::control_type() const {
  // @@protoc_insertion_point(field_get:Data.SnakeCreateData.control_type)
  return static_cast< ::Data::ControlType >(control_type_);
}
void SnakeCreateData::set_control_type(::Data::ControlType value) {
  assert(::Data::ControlType_IsValid(value));
  set_has_control_type();
  control_type_ = value;
  // @@protoc_insertion_point(field_set:Data.SnakeCreateData.control_type)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Data

// @@protoc_insertion_point(global_scope)
