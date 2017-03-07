// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CommandData.proto

#ifndef PROTOBUF_CommandData_2eproto__INCLUDED
#define PROTOBUF_CommandData_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3002000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3002000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
#include "Base.pb.h"
// @@protoc_insertion_point(includes)
namespace Data {
class CommandData;
class CommandDataDefaultTypeInternal;
extern CommandDataDefaultTypeInternal _CommandData_default_instance_;
class Vec2;
class Vec2DefaultTypeInternal;
extern Vec2DefaultTypeInternal _Vec2_default_instance_;
}  // namespace Data

namespace Data {

namespace protobuf_CommandData_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_CommandData_2eproto

// ===================================================================

class CommandData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Data.CommandData) */ {
 public:
  CommandData();
  virtual ~CommandData();

  CommandData(const CommandData& from);

  inline CommandData& operator=(const CommandData& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CommandData& default_instance();

  static inline const CommandData* internal_default_instance() {
    return reinterpret_cast<const CommandData*>(
               &_CommandData_default_instance_);
  }

  void Swap(CommandData* other);

  // implements Message ----------------------------------------------

  inline CommandData* New() const PROTOBUF_FINAL { return New(NULL); }

  CommandData* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const CommandData& from);
  void MergeFrom(const CommandData& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output)
      const PROTOBUF_FINAL {
    return InternalSerializeWithCachedSizesToArray(
        ::google::protobuf::io::CodedOutputStream::IsDefaultSerializationDeterministic(), output);
  }
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(CommandData* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required .Data.Command command = 1;
  bool has_command() const;
  void clear_command();
  static const int kCommandFieldNumber = 1;
  ::Data::Command command() const;
  void set_command(::Data::Command value);

  // @@protoc_insertion_point(class_scope:Data.CommandData)
 private:
  void set_has_command();
  void clear_has_command();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  int command_;
  friend struct  protobuf_CommandData_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// CommandData

// required .Data.Command command = 1;
inline bool CommandData::has_command() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void CommandData::set_has_command() {
  _has_bits_[0] |= 0x00000001u;
}
inline void CommandData::clear_has_command() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void CommandData::clear_command() {
  command_ = 0;
  clear_has_command();
}
inline ::Data::Command CommandData::command() const {
  // @@protoc_insertion_point(field_get:Data.CommandData.command)
  return static_cast< ::Data::Command >(command_);
}
inline void CommandData::set_command(::Data::Command value) {
  assert(::Data::Command_IsValid(value));
  set_has_command();
  command_ = value;
  // @@protoc_insertion_point(field_set:Data.CommandData.command)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace Data

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_CommandData_2eproto__INCLUDED
