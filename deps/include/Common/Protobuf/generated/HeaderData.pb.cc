// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: HeaderData.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "HeaderData.pb.h"

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
class HeaderDataDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<HeaderData> {
} _HeaderData_default_instance_;

namespace protobuf_HeaderData_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];

}  // namespace

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HeaderData, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HeaderData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HeaderData, size_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(HeaderData, type_),
  0,
  1,
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 6, sizeof(HeaderData)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_HeaderData_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "HeaderData.proto", schemas, file_default_instances, TableStruct::offsets, factory,
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
  _HeaderData_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  _HeaderData_default_instance_.DefaultConstruct();
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\020HeaderData.proto\022\004Data\"(\n\nHeaderData\022\014"
      "\n\004size\030\001 \002(\007\022\014\n\004type\030\002 \002(\007"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 66);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "HeaderData.proto", &protobuf_RegisterTypes);
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

}  // namespace protobuf_HeaderData_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int HeaderData::kSizeFieldNumber;
const int HeaderData::kTypeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

HeaderData::HeaderData()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_HeaderData_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:Data.HeaderData)
}
HeaderData::HeaderData(const HeaderData& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&size_, &from.size_,
    reinterpret_cast<char*>(&type_) -
    reinterpret_cast<char*>(&size_) + sizeof(type_));
  // @@protoc_insertion_point(copy_constructor:Data.HeaderData)
}

void HeaderData::SharedCtor() {
  _cached_size_ = 0;
  ::memset(&size_, 0, reinterpret_cast<char*>(&type_) -
    reinterpret_cast<char*>(&size_) + sizeof(type_));
}

HeaderData::~HeaderData() {
  // @@protoc_insertion_point(destructor:Data.HeaderData)
  SharedDtor();
}

void HeaderData::SharedDtor() {
}

void HeaderData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* HeaderData::descriptor() {
  protobuf_HeaderData_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_HeaderData_2eproto::file_level_metadata[0].descriptor;
}

const HeaderData& HeaderData::default_instance() {
  protobuf_HeaderData_2eproto::InitDefaults();
  return *internal_default_instance();
}

HeaderData* HeaderData::New(::google::protobuf::Arena* arena) const {
  HeaderData* n = new HeaderData;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void HeaderData::Clear() {
// @@protoc_insertion_point(message_clear_start:Data.HeaderData)
  if (_has_bits_[0 / 32] & 3u) {
    ::memset(&size_, 0, reinterpret_cast<char*>(&type_) -
      reinterpret_cast<char*>(&size_) + sizeof(type_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool HeaderData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Data.HeaderData)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required fixed32 size = 1;
      case 1: {
        if (tag == 13u) {
          set_has_size();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_FIXED32>(
                 input, &size_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required fixed32 type = 2;
      case 2: {
        if (tag == 21u) {
          set_has_type();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_FIXED32>(
                 input, &type_)));
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
  // @@protoc_insertion_point(parse_success:Data.HeaderData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Data.HeaderData)
  return false;
#undef DO_
}

void HeaderData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Data.HeaderData)
  // required fixed32 size = 1;
  if (has_size()) {
    ::google::protobuf::internal::WireFormatLite::WriteFixed32(1, this->size(), output);
  }

  // required fixed32 type = 2;
  if (has_type()) {
    ::google::protobuf::internal::WireFormatLite::WriteFixed32(2, this->type(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Data.HeaderData)
}

::google::protobuf::uint8* HeaderData::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic;  // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Data.HeaderData)
  // required fixed32 size = 1;
  if (has_size()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFixed32ToArray(1, this->size(), target);
  }

  // required fixed32 type = 2;
  if (has_type()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteFixed32ToArray(2, this->type(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Data.HeaderData)
  return target;
}

size_t HeaderData::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:Data.HeaderData)
  size_t total_size = 0;

  if (has_size()) {
    // required fixed32 size = 1;
    total_size += 1 + 4;
  }

  if (has_type()) {
    // required fixed32 type = 2;
    total_size += 1 + 4;
  }

  return total_size;
}
size_t HeaderData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Data.HeaderData)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required fixed32 size = 1;
    total_size += 1 + 4;

    // required fixed32 type = 2;
    total_size += 1 + 4;

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void HeaderData::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Data.HeaderData)
  GOOGLE_DCHECK_NE(&from, this);
  const HeaderData* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const HeaderData>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Data.HeaderData)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Data.HeaderData)
    MergeFrom(*source);
  }
}

void HeaderData::MergeFrom(const HeaderData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Data.HeaderData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from._has_bits_[0 / 32] & 3u) {
    if (from.has_size()) {
      set_size(from.size());
    }
    if (from.has_type()) {
      set_type(from.type());
    }
  }
}

void HeaderData::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Data.HeaderData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void HeaderData::CopyFrom(const HeaderData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Data.HeaderData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HeaderData::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  return true;
}

void HeaderData::Swap(HeaderData* other) {
  if (other == this) return;
  InternalSwap(other);
}
void HeaderData::InternalSwap(HeaderData* other) {
  std::swap(size_, other->size_);
  std::swap(type_, other->type_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata HeaderData::GetMetadata() const {
  protobuf_HeaderData_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_HeaderData_2eproto::file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// HeaderData

// required fixed32 size = 1;
bool HeaderData::has_size() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void HeaderData::set_has_size() {
  _has_bits_[0] |= 0x00000001u;
}
void HeaderData::clear_has_size() {
  _has_bits_[0] &= ~0x00000001u;
}
void HeaderData::clear_size() {
  size_ = 0u;
  clear_has_size();
}
::google::protobuf::uint32 HeaderData::size() const {
  // @@protoc_insertion_point(field_get:Data.HeaderData.size)
  return size_;
}
void HeaderData::set_size(::google::protobuf::uint32 value) {
  set_has_size();
  size_ = value;
  // @@protoc_insertion_point(field_set:Data.HeaderData.size)
}

// required fixed32 type = 2;
bool HeaderData::has_type() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void HeaderData::set_has_type() {
  _has_bits_[0] |= 0x00000002u;
}
void HeaderData::clear_has_type() {
  _has_bits_[0] &= ~0x00000002u;
}
void HeaderData::clear_type() {
  type_ = 0u;
  clear_has_type();
}
::google::protobuf::uint32 HeaderData::type() const {
  // @@protoc_insertion_point(field_get:Data.HeaderData.type)
  return type_;
}
void HeaderData::set_type(::google::protobuf::uint32 value) {
  set_has_type();
  type_ = value;
  // @@protoc_insertion_point(field_set:Data.HeaderData.type)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Data

// @@protoc_insertion_point(global_scope)
