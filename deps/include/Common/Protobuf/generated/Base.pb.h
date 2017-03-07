// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Base.proto

#ifndef PROTOBUF_Base_2eproto__INCLUDED
#define PROTOBUF_Base_2eproto__INCLUDED

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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace Data {
class Vec2;
class Vec2DefaultTypeInternal;
extern Vec2DefaultTypeInternal _Vec2_default_instance_;
}  // namespace Data

namespace Data {

namespace protobuf_Base_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_Base_2eproto

enum PacketType {
  RequestConnect = 0,
  Full = 1,
  InitGame = 2,
  ReadyToJoin = 3,
  Intro = 4,
  Joined = 5,
  Disconnected = 6,
  NotifyDisconnected = 7,
  ChangeLevel = 8,
  ReadyToChange = 9,
  EnterPlaying = 10,
  Replicate = 11,
  ClientCommand = 12
};
bool PacketType_IsValid(int value);
const PacketType PacketType_MIN = RequestConnect;
const PacketType PacketType_MAX = ClientCommand;
const int PacketType_ARRAYSIZE = PacketType_MAX + 1;

const ::google::protobuf::EnumDescriptor* PacketType_descriptor();
inline const ::std::string& PacketType_Name(PacketType value) {
  return ::google::protobuf::internal::NameOfEnum(
    PacketType_descriptor(), value);
}
inline bool PacketType_Parse(
    const ::std::string& name, PacketType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<PacketType>(
    PacketType_descriptor(), name, value);
}
enum ControlType {
  NPC = 0,
  AI = 1,
  Player = 2
};
bool ControlType_IsValid(int value);
const ControlType ControlType_MIN = NPC;
const ControlType ControlType_MAX = Player;
const int ControlType_ARRAYSIZE = ControlType_MAX + 1;

const ::google::protobuf::EnumDescriptor* ControlType_descriptor();
inline const ::std::string& ControlType_Name(ControlType value) {
  return ::google::protobuf::internal::NameOfEnum(
    ControlType_descriptor(), value);
}
inline bool ControlType_Parse(
    const ::std::string& name, ControlType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<ControlType>(
    ControlType_descriptor(), name, value);
}
enum CommandType {
  MoveLeft = 0,
  MoveRight = 1,
  MoveUp = 2,
  MoveDown = 3
};
bool CommandType_IsValid(int value);
const CommandType CommandType_MIN = MoveLeft;
const CommandType CommandType_MAX = MoveDown;
const int CommandType_ARRAYSIZE = CommandType_MAX + 1;

const ::google::protobuf::EnumDescriptor* CommandType_descriptor();
inline const ::std::string& CommandType_Name(CommandType value) {
  return ::google::protobuf::internal::NameOfEnum(
    CommandType_descriptor(), value);
}
inline bool CommandType_Parse(
    const ::std::string& name, CommandType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<CommandType>(
    CommandType_descriptor(), name, value);
}
// ===================================================================

class Vec2 : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Data.Vec2) */ {
 public:
  Vec2();
  virtual ~Vec2();

  Vec2(const Vec2& from);

  inline Vec2& operator=(const Vec2& from) {
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
  static const Vec2& default_instance();

  static inline const Vec2* internal_default_instance() {
    return reinterpret_cast<const Vec2*>(
               &_Vec2_default_instance_);
  }

  void Swap(Vec2* other);

  // implements Message ----------------------------------------------

  inline Vec2* New() const PROTOBUF_FINAL { return New(NULL); }

  Vec2* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const Vec2& from);
  void MergeFrom(const Vec2& from);
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
  void InternalSwap(Vec2* other);
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

  // required float x = 1;
  bool has_x() const;
  void clear_x();
  static const int kXFieldNumber = 1;
  float x() const;
  void set_x(float value);

  // required float y = 2;
  bool has_y() const;
  void clear_y();
  static const int kYFieldNumber = 2;
  float y() const;
  void set_y(float value);

  // @@protoc_insertion_point(class_scope:Data.Vec2)
 private:
  void set_has_x();
  void clear_has_x();
  void set_has_y();
  void clear_has_y();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  float x_;
  float y_;
  friend struct  protobuf_Base_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Vec2

// required float x = 1;
inline bool Vec2::has_x() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Vec2::set_has_x() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Vec2::clear_has_x() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Vec2::clear_x() {
  x_ = 0;
  clear_has_x();
}
inline float Vec2::x() const {
  // @@protoc_insertion_point(field_get:Data.Vec2.x)
  return x_;
}
inline void Vec2::set_x(float value) {
  set_has_x();
  x_ = value;
  // @@protoc_insertion_point(field_set:Data.Vec2.x)
}

// required float y = 2;
inline bool Vec2::has_y() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Vec2::set_has_y() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Vec2::clear_has_y() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Vec2::clear_y() {
  y_ = 0;
  clear_has_y();
}
inline float Vec2::y() const {
  // @@protoc_insertion_point(field_get:Data.Vec2.y)
  return y_;
}
inline void Vec2::set_y(float value) {
  set_has_y();
  y_ = value;
  // @@protoc_insertion_point(field_set:Data.Vec2.y)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace Data

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::Data::PacketType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Data::PacketType>() {
  return ::Data::PacketType_descriptor();
}
template <> struct is_proto_enum< ::Data::ControlType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Data::ControlType>() {
  return ::Data::ControlType_descriptor();
}
template <> struct is_proto_enum< ::Data::CommandType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Data::CommandType>() {
  return ::Data::CommandType_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Base_2eproto__INCLUDED
