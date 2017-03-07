// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProjectileUpdateData.proto

#ifndef PROTOBUF_ProjectileUpdateData_2eproto__INCLUDED
#define PROTOBUF_ProjectileUpdateData_2eproto__INCLUDED

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
class ProjectileUpdateData;
class ProjectileUpdateDataDefaultTypeInternal;
extern ProjectileUpdateDataDefaultTypeInternal _ProjectileUpdateData_default_instance_;
class Vec2;
class Vec2DefaultTypeInternal;
extern Vec2DefaultTypeInternal _Vec2_default_instance_;
}  // namespace Data

namespace Data {

namespace protobuf_ProjectileUpdateData_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_ProjectileUpdateData_2eproto

// ===================================================================

class ProjectileUpdateData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Data.ProjectileUpdateData) */ {
 public:
  ProjectileUpdateData();
  virtual ~ProjectileUpdateData();

  ProjectileUpdateData(const ProjectileUpdateData& from);

  inline ProjectileUpdateData& operator=(const ProjectileUpdateData& from) {
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
  static const ProjectileUpdateData& default_instance();

  static inline const ProjectileUpdateData* internal_default_instance() {
    return reinterpret_cast<const ProjectileUpdateData*>(
               &_ProjectileUpdateData_default_instance_);
  }

  void Swap(ProjectileUpdateData* other);

  // implements Message ----------------------------------------------

  inline ProjectileUpdateData* New() const PROTOBUF_FINAL { return New(NULL); }

  ProjectileUpdateData* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const ProjectileUpdateData& from);
  void MergeFrom(const ProjectileUpdateData& from);
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
  void InternalSwap(ProjectileUpdateData* other);
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

  // required .Data.Vec2 pos = 2;
  bool has_pos() const;
  void clear_pos();
  static const int kPosFieldNumber = 2;
  const ::Data::Vec2& pos() const;
  ::Data::Vec2* mutable_pos();
  ::Data::Vec2* release_pos();
  void set_allocated_pos(::Data::Vec2* pos);

  // required int32 entity_id = 1;
  bool has_entity_id() const;
  void clear_entity_id();
  static const int kEntityIdFieldNumber = 1;
  ::google::protobuf::int32 entity_id() const;
  void set_entity_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Data.ProjectileUpdateData)
 private:
  void set_has_entity_id();
  void clear_has_entity_id();
  void set_has_pos();
  void clear_has_pos();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::Data::Vec2* pos_;
  ::google::protobuf::int32 entity_id_;
  friend struct  protobuf_ProjectileUpdateData_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ProjectileUpdateData

// required int32 entity_id = 1;
inline bool ProjectileUpdateData::has_entity_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ProjectileUpdateData::set_has_entity_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ProjectileUpdateData::clear_has_entity_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ProjectileUpdateData::clear_entity_id() {
  entity_id_ = 0;
  clear_has_entity_id();
}
inline ::google::protobuf::int32 ProjectileUpdateData::entity_id() const {
  // @@protoc_insertion_point(field_get:Data.ProjectileUpdateData.entity_id)
  return entity_id_;
}
inline void ProjectileUpdateData::set_entity_id(::google::protobuf::int32 value) {
  set_has_entity_id();
  entity_id_ = value;
  // @@protoc_insertion_point(field_set:Data.ProjectileUpdateData.entity_id)
}

// required .Data.Vec2 pos = 2;
inline bool ProjectileUpdateData::has_pos() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ProjectileUpdateData::set_has_pos() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ProjectileUpdateData::clear_has_pos() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ProjectileUpdateData::clear_pos() {
  if (pos_ != NULL) pos_->::Data::Vec2::Clear();
  clear_has_pos();
}
inline const ::Data::Vec2& ProjectileUpdateData::pos() const {
  // @@protoc_insertion_point(field_get:Data.ProjectileUpdateData.pos)
  return pos_ != NULL ? *pos_
                         : *::Data::Vec2::internal_default_instance();
}
inline ::Data::Vec2* ProjectileUpdateData::mutable_pos() {
  set_has_pos();
  if (pos_ == NULL) {
    pos_ = new ::Data::Vec2;
  }
  // @@protoc_insertion_point(field_mutable:Data.ProjectileUpdateData.pos)
  return pos_;
}
inline ::Data::Vec2* ProjectileUpdateData::release_pos() {
  // @@protoc_insertion_point(field_release:Data.ProjectileUpdateData.pos)
  clear_has_pos();
  ::Data::Vec2* temp = pos_;
  pos_ = NULL;
  return temp;
}
inline void ProjectileUpdateData::set_allocated_pos(::Data::Vec2* pos) {
  delete pos_;
  pos_ = pos;
  if (pos) {
    set_has_pos();
  } else {
    clear_has_pos();
  }
  // @@protoc_insertion_point(field_set_allocated:Data.ProjectileUpdateData.pos)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace Data

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ProjectileUpdateData_2eproto__INCLUDED
