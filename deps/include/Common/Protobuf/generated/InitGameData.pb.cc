// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: InitGameData.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "InitGameData.pb.h"

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
class InitGameDataDefaultTypeInternal : public ::google::protobuf::internal::ExplicitlyConstructed<InitGameData> {
} _InitGameData_default_instance_;

namespace protobuf_InitGameData_2eproto {


namespace {

::google::protobuf::Metadata file_level_metadata[1];

}  // namespace

const ::google::protobuf::uint32 TableStruct::offsets[] = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(InitGameData, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(InitGameData, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(InitGameData, creates_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(InitGameData, level_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(InitGameData, joined_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(InitGameData, others_),
  0,
  3,
  1,
  2,
};

static const ::google::protobuf::internal::MigrationSchema schemas[] = {
  { 0, 8, sizeof(InitGameData)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&_InitGameData_default_instance_),
};

namespace {

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "InitGameData.proto", schemas, file_default_instances, TableStruct::offsets, factory,
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
  _InitGameData_default_instance_.Shutdown();
  delete file_level_metadata[0].reflection;
}

void TableStruct::InitDefaultsImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::InitProtobufDefaults();
  ::Data::protobuf_CreateData_2eproto::InitDefaults();
  ::Data::protobuf_UserData_2eproto::InitDefaults();
  ::Data::protobuf_JoinedData_2eproto::InitDefaults();
  _InitGameData_default_instance_.DefaultConstruct();
  _InitGameData_default_instance_.get_mutable()->creates_ = const_cast< ::Data::CreateData*>(
      ::Data::CreateData::internal_default_instance());
  _InitGameData_default_instance_.get_mutable()->joined_ = const_cast< ::Data::UserData*>(
      ::Data::UserData::internal_default_instance());
  _InitGameData_default_instance_.get_mutable()->others_ = const_cast< ::Data::JoinedData*>(
      ::Data::JoinedData::internal_default_instance());
}

void InitDefaults() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &TableStruct::InitDefaultsImpl);
}
void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] = {
      "\n\022InitGameData.proto\022\004Data\032\020CreateData.p"
      "roto\032\016UserData.proto\032\020JoinedData.proto\"\202"
      "\001\n\014InitGameData\022!\n\007creates\030\001 \002(\0132\020.Data."
      "CreateData\022\r\n\005level\030\002 \002(\r\022\036\n\006joined\030\003 \002("
      "\0132\016.Data.UserData\022 \n\006others\030\004 \002(\0132\020.Data"
      ".JoinedData"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 211);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "InitGameData.proto", &protobuf_RegisterTypes);
  ::Data::protobuf_CreateData_2eproto::AddDescriptors();
  ::Data::protobuf_UserData_2eproto::AddDescriptors();
  ::Data::protobuf_JoinedData_2eproto::AddDescriptors();
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

}  // namespace protobuf_InitGameData_2eproto


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int InitGameData::kCreatesFieldNumber;
const int InitGameData::kLevelFieldNumber;
const int InitGameData::kJoinedFieldNumber;
const int InitGameData::kOthersFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

InitGameData::InitGameData()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    protobuf_InitGameData_2eproto::InitDefaults();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:Data.InitGameData)
}
InitGameData::InitGameData(const InitGameData& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from.has_creates()) {
    creates_ = new ::Data::CreateData(*from.creates_);
  } else {
    creates_ = NULL;
  }
  if (from.has_joined()) {
    joined_ = new ::Data::UserData(*from.joined_);
  } else {
    joined_ = NULL;
  }
  if (from.has_others()) {
    others_ = new ::Data::JoinedData(*from.others_);
  } else {
    others_ = NULL;
  }
  level_ = from.level_;
  // @@protoc_insertion_point(copy_constructor:Data.InitGameData)
}

void InitGameData::SharedCtor() {
  _cached_size_ = 0;
  ::memset(&creates_, 0, reinterpret_cast<char*>(&level_) -
    reinterpret_cast<char*>(&creates_) + sizeof(level_));
}

InitGameData::~InitGameData() {
  // @@protoc_insertion_point(destructor:Data.InitGameData)
  SharedDtor();
}

void InitGameData::SharedDtor() {
  if (this != internal_default_instance()) {
    delete creates_;
  }
  if (this != internal_default_instance()) {
    delete joined_;
  }
  if (this != internal_default_instance()) {
    delete others_;
  }
}

void InitGameData::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* InitGameData::descriptor() {
  protobuf_InitGameData_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_InitGameData_2eproto::file_level_metadata[0].descriptor;
}

const InitGameData& InitGameData::default_instance() {
  protobuf_InitGameData_2eproto::InitDefaults();
  return *internal_default_instance();
}

InitGameData* InitGameData::New(::google::protobuf::Arena* arena) const {
  InitGameData* n = new InitGameData;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void InitGameData::Clear() {
// @@protoc_insertion_point(message_clear_start:Data.InitGameData)
  if (_has_bits_[0 / 32] & 7u) {
    if (has_creates()) {
      GOOGLE_DCHECK(creates_ != NULL);
      creates_->::Data::CreateData::Clear();
    }
    if (has_joined()) {
      GOOGLE_DCHECK(joined_ != NULL);
      joined_->::Data::UserData::Clear();
    }
    if (has_others()) {
      GOOGLE_DCHECK(others_ != NULL);
      others_->::Data::JoinedData::Clear();
    }
  }
  level_ = 0u;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool InitGameData::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:Data.InitGameData)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .Data.CreateData creates = 1;
      case 1: {
        if (tag == 10u) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_creates()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required uint32 level = 2;
      case 2: {
        if (tag == 16u) {
          set_has_level();
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &level_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required .Data.UserData joined = 3;
      case 3: {
        if (tag == 26u) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_joined()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required .Data.JoinedData others = 4;
      case 4: {
        if (tag == 34u) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
               input, mutable_others()));
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
  // @@protoc_insertion_point(parse_success:Data.InitGameData)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:Data.InitGameData)
  return false;
#undef DO_
}

void InitGameData::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:Data.InitGameData)
  // required .Data.CreateData creates = 1;
  if (has_creates()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, *this->creates_, output);
  }

  // required uint32 level = 2;
  if (has_level()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->level(), output);
  }

  // required .Data.UserData joined = 3;
  if (has_joined()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      3, *this->joined_, output);
  }

  // required .Data.JoinedData others = 4;
  if (has_others()) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      4, *this->others_, output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:Data.InitGameData)
}

::google::protobuf::uint8* InitGameData::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic;  // Unused
  // @@protoc_insertion_point(serialize_to_array_start:Data.InitGameData)
  // required .Data.CreateData creates = 1;
  if (has_creates()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        1, *this->creates_, false, target);
  }

  // required uint32 level = 2;
  if (has_level()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->level(), target);
  }

  // required .Data.UserData joined = 3;
  if (has_joined()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        3, *this->joined_, false, target);
  }

  // required .Data.JoinedData others = 4;
  if (has_others()) {
    target = ::google::protobuf::internal::WireFormatLite::
      InternalWriteMessageNoVirtualToArray(
        4, *this->others_, false, target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Data.InitGameData)
  return target;
}

size_t InitGameData::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:Data.InitGameData)
  size_t total_size = 0;

  if (has_creates()) {
    // required .Data.CreateData creates = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->creates_);
  }

  if (has_joined()) {
    // required .Data.UserData joined = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->joined_);
  }

  if (has_others()) {
    // required .Data.JoinedData others = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->others_);
  }

  if (has_level()) {
    // required uint32 level = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->level());
  }

  return total_size;
}
size_t InitGameData::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Data.InitGameData)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  if (((_has_bits_[0] & 0x0000000f) ^ 0x0000000f) == 0) {  // All required fields are present.
    // required .Data.CreateData creates = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->creates_);

    // required .Data.UserData joined = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->joined_);

    // required .Data.JoinedData others = 4;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        *this->others_);

    // required uint32 level = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->level());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void InitGameData::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:Data.InitGameData)
  GOOGLE_DCHECK_NE(&from, this);
  const InitGameData* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const InitGameData>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:Data.InitGameData)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:Data.InitGameData)
    MergeFrom(*source);
  }
}

void InitGameData::MergeFrom(const InitGameData& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:Data.InitGameData)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from._has_bits_[0 / 32] & 15u) {
    if (from.has_creates()) {
      mutable_creates()->::Data::CreateData::MergeFrom(from.creates());
    }
    if (from.has_joined()) {
      mutable_joined()->::Data::UserData::MergeFrom(from.joined());
    }
    if (from.has_others()) {
      mutable_others()->::Data::JoinedData::MergeFrom(from.others());
    }
    if (from.has_level()) {
      set_level(from.level());
    }
  }
}

void InitGameData::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:Data.InitGameData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void InitGameData::CopyFrom(const InitGameData& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Data.InitGameData)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool InitGameData::IsInitialized() const {
  if ((_has_bits_[0] & 0x0000000f) != 0x0000000f) return false;
  if (has_creates()) {
    if (!this->creates_->IsInitialized()) return false;
  }
  if (has_joined()) {
    if (!this->joined_->IsInitialized()) return false;
  }
  if (has_others()) {
    if (!this->others_->IsInitialized()) return false;
  }
  return true;
}

void InitGameData::Swap(InitGameData* other) {
  if (other == this) return;
  InternalSwap(other);
}
void InitGameData::InternalSwap(InitGameData* other) {
  std::swap(creates_, other->creates_);
  std::swap(joined_, other->joined_);
  std::swap(others_, other->others_);
  std::swap(level_, other->level_);
  std::swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata InitGameData::GetMetadata() const {
  protobuf_InitGameData_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_InitGameData_2eproto::file_level_metadata[0];
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// InitGameData

// required .Data.CreateData creates = 1;
bool InitGameData::has_creates() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
void InitGameData::set_has_creates() {
  _has_bits_[0] |= 0x00000001u;
}
void InitGameData::clear_has_creates() {
  _has_bits_[0] &= ~0x00000001u;
}
void InitGameData::clear_creates() {
  if (creates_ != NULL) creates_->::Data::CreateData::Clear();
  clear_has_creates();
}
const ::Data::CreateData& InitGameData::creates() const {
  // @@protoc_insertion_point(field_get:Data.InitGameData.creates)
  return creates_ != NULL ? *creates_
                         : *::Data::CreateData::internal_default_instance();
}
::Data::CreateData* InitGameData::mutable_creates() {
  set_has_creates();
  if (creates_ == NULL) {
    creates_ = new ::Data::CreateData;
  }
  // @@protoc_insertion_point(field_mutable:Data.InitGameData.creates)
  return creates_;
}
::Data::CreateData* InitGameData::release_creates() {
  // @@protoc_insertion_point(field_release:Data.InitGameData.creates)
  clear_has_creates();
  ::Data::CreateData* temp = creates_;
  creates_ = NULL;
  return temp;
}
void InitGameData::set_allocated_creates(::Data::CreateData* creates) {
  delete creates_;
  creates_ = creates;
  if (creates) {
    set_has_creates();
  } else {
    clear_has_creates();
  }
  // @@protoc_insertion_point(field_set_allocated:Data.InitGameData.creates)
}

// required uint32 level = 2;
bool InitGameData::has_level() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
void InitGameData::set_has_level() {
  _has_bits_[0] |= 0x00000008u;
}
void InitGameData::clear_has_level() {
  _has_bits_[0] &= ~0x00000008u;
}
void InitGameData::clear_level() {
  level_ = 0u;
  clear_has_level();
}
::google::protobuf::uint32 InitGameData::level() const {
  // @@protoc_insertion_point(field_get:Data.InitGameData.level)
  return level_;
}
void InitGameData::set_level(::google::protobuf::uint32 value) {
  set_has_level();
  level_ = value;
  // @@protoc_insertion_point(field_set:Data.InitGameData.level)
}

// required .Data.UserData joined = 3;
bool InitGameData::has_joined() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
void InitGameData::set_has_joined() {
  _has_bits_[0] |= 0x00000002u;
}
void InitGameData::clear_has_joined() {
  _has_bits_[0] &= ~0x00000002u;
}
void InitGameData::clear_joined() {
  if (joined_ != NULL) joined_->::Data::UserData::Clear();
  clear_has_joined();
}
const ::Data::UserData& InitGameData::joined() const {
  // @@protoc_insertion_point(field_get:Data.InitGameData.joined)
  return joined_ != NULL ? *joined_
                         : *::Data::UserData::internal_default_instance();
}
::Data::UserData* InitGameData::mutable_joined() {
  set_has_joined();
  if (joined_ == NULL) {
    joined_ = new ::Data::UserData;
  }
  // @@protoc_insertion_point(field_mutable:Data.InitGameData.joined)
  return joined_;
}
::Data::UserData* InitGameData::release_joined() {
  // @@protoc_insertion_point(field_release:Data.InitGameData.joined)
  clear_has_joined();
  ::Data::UserData* temp = joined_;
  joined_ = NULL;
  return temp;
}
void InitGameData::set_allocated_joined(::Data::UserData* joined) {
  delete joined_;
  joined_ = joined;
  if (joined) {
    set_has_joined();
  } else {
    clear_has_joined();
  }
  // @@protoc_insertion_point(field_set_allocated:Data.InitGameData.joined)
}

// required .Data.JoinedData others = 4;
bool InitGameData::has_others() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
void InitGameData::set_has_others() {
  _has_bits_[0] |= 0x00000004u;
}
void InitGameData::clear_has_others() {
  _has_bits_[0] &= ~0x00000004u;
}
void InitGameData::clear_others() {
  if (others_ != NULL) others_->::Data::JoinedData::Clear();
  clear_has_others();
}
const ::Data::JoinedData& InitGameData::others() const {
  // @@protoc_insertion_point(field_get:Data.InitGameData.others)
  return others_ != NULL ? *others_
                         : *::Data::JoinedData::internal_default_instance();
}
::Data::JoinedData* InitGameData::mutable_others() {
  set_has_others();
  if (others_ == NULL) {
    others_ = new ::Data::JoinedData;
  }
  // @@protoc_insertion_point(field_mutable:Data.InitGameData.others)
  return others_;
}
::Data::JoinedData* InitGameData::release_others() {
  // @@protoc_insertion_point(field_release:Data.InitGameData.others)
  clear_has_others();
  ::Data::JoinedData* temp = others_;
  others_ = NULL;
  return temp;
}
void InitGameData::set_allocated_others(::Data::JoinedData* others) {
  delete others_;
  others_ = others;
  if (others) {
    set_has_others();
  } else {
    clear_has_others();
  }
  // @@protoc_insertion_point(field_set_allocated:Data.InitGameData.others)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace Data

// @@protoc_insertion_point(global_scope)
