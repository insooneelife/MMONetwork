// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: UpdateData.proto

#ifndef PROTOBUF_UpdateData_2eproto__INCLUDED
#define PROTOBUF_UpdateData_2eproto__INCLUDED

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
#include "EntityUpdateData.pb.h"
#include "UserData.pb.h"
// @@protoc_insertion_point(includes)
namespace Data {
class EntityUpdateData;
class EntityUpdateDataDefaultTypeInternal;
extern EntityUpdateDataDefaultTypeInternal _EntityUpdateData_default_instance_;
class UpdateData;
class UpdateDataDefaultTypeInternal;
extern UpdateDataDefaultTypeInternal _UpdateData_default_instance_;
class UserData;
class UserDataDefaultTypeInternal;
extern UserDataDefaultTypeInternal _UserData_default_instance_;
}  // namespace Data

namespace Data {

namespace protobuf_UpdateData_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_UpdateData_2eproto

// ===================================================================

class UpdateData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Data.UpdateData) */ {
 public:
  UpdateData();
  virtual ~UpdateData();

  UpdateData(const UpdateData& from);

  inline UpdateData& operator=(const UpdateData& from) {
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
  static const UpdateData& default_instance();

  static inline const UpdateData* internal_default_instance() {
    return reinterpret_cast<const UpdateData*>(
               &_UpdateData_default_instance_);
  }

  void Swap(UpdateData* other);

  // implements Message ----------------------------------------------

  inline UpdateData* New() const PROTOBUF_FINAL { return New(NULL); }

  UpdateData* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const UpdateData& from);
  void MergeFrom(const UpdateData& from);
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
  void InternalSwap(UpdateData* other);
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

  // repeated .Data.EntityUpdateData updated_entities = 1;
  int updated_entities_size() const;
  void clear_updated_entities();
  static const int kUpdatedEntitiesFieldNumber = 1;
  const ::Data::EntityUpdateData& updated_entities(int index) const;
  ::Data::EntityUpdateData* mutable_updated_entities(int index);
  ::Data::EntityUpdateData* add_updated_entities();
  ::google::protobuf::RepeatedPtrField< ::Data::EntityUpdateData >*
      mutable_updated_entities();
  const ::google::protobuf::RepeatedPtrField< ::Data::EntityUpdateData >&
      updated_entities() const;

  // repeated .Data.UserData updated_users = 2;
  int updated_users_size() const;
  void clear_updated_users();
  static const int kUpdatedUsersFieldNumber = 2;
  const ::Data::UserData& updated_users(int index) const;
  ::Data::UserData* mutable_updated_users(int index);
  ::Data::UserData* add_updated_users();
  ::google::protobuf::RepeatedPtrField< ::Data::UserData >*
      mutable_updated_users();
  const ::google::protobuf::RepeatedPtrField< ::Data::UserData >&
      updated_users() const;

  // @@protoc_insertion_point(class_scope:Data.UpdateData)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::Data::EntityUpdateData > updated_entities_;
  ::google::protobuf::RepeatedPtrField< ::Data::UserData > updated_users_;
  friend struct  protobuf_UpdateData_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// UpdateData

// repeated .Data.EntityUpdateData updated_entities = 1;
inline int UpdateData::updated_entities_size() const {
  return updated_entities_.size();
}
inline void UpdateData::clear_updated_entities() {
  updated_entities_.Clear();
}
inline const ::Data::EntityUpdateData& UpdateData::updated_entities(int index) const {
  // @@protoc_insertion_point(field_get:Data.UpdateData.updated_entities)
  return updated_entities_.Get(index);
}
inline ::Data::EntityUpdateData* UpdateData::mutable_updated_entities(int index) {
  // @@protoc_insertion_point(field_mutable:Data.UpdateData.updated_entities)
  return updated_entities_.Mutable(index);
}
inline ::Data::EntityUpdateData* UpdateData::add_updated_entities() {
  // @@protoc_insertion_point(field_add:Data.UpdateData.updated_entities)
  return updated_entities_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::Data::EntityUpdateData >*
UpdateData::mutable_updated_entities() {
  // @@protoc_insertion_point(field_mutable_list:Data.UpdateData.updated_entities)
  return &updated_entities_;
}
inline const ::google::protobuf::RepeatedPtrField< ::Data::EntityUpdateData >&
UpdateData::updated_entities() const {
  // @@protoc_insertion_point(field_list:Data.UpdateData.updated_entities)
  return updated_entities_;
}

// repeated .Data.UserData updated_users = 2;
inline int UpdateData::updated_users_size() const {
  return updated_users_.size();
}
inline void UpdateData::clear_updated_users() {
  updated_users_.Clear();
}
inline const ::Data::UserData& UpdateData::updated_users(int index) const {
  // @@protoc_insertion_point(field_get:Data.UpdateData.updated_users)
  return updated_users_.Get(index);
}
inline ::Data::UserData* UpdateData::mutable_updated_users(int index) {
  // @@protoc_insertion_point(field_mutable:Data.UpdateData.updated_users)
  return updated_users_.Mutable(index);
}
inline ::Data::UserData* UpdateData::add_updated_users() {
  // @@protoc_insertion_point(field_add:Data.UpdateData.updated_users)
  return updated_users_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::Data::UserData >*
UpdateData::mutable_updated_users() {
  // @@protoc_insertion_point(field_mutable_list:Data.UpdateData.updated_users)
  return &updated_users_;
}
inline const ::google::protobuf::RepeatedPtrField< ::Data::UserData >&
UpdateData::updated_users() const {
  // @@protoc_insertion_point(field_list:Data.UpdateData.updated_users)
  return updated_users_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace Data

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_UpdateData_2eproto__INCLUDED
