// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PB_Eotq.proto3

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "PB_Eotq.proto3.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace PB_Eotq {

namespace {

const ::google::protobuf::Descriptor* MsgResouces_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  MsgResouces_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_PB_5fEotq_2eproto3() {
  protobuf_AddDesc_PB_5fEotq_2eproto3();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "PB_Eotq.proto3");
  GOOGLE_CHECK(file != NULL);
  MsgResouces_descriptor_ = file->message_type(0);
  static const int MsgResouces_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MsgResouces, lck_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MsgResouces, rck_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MsgResouces, val_),
  };
  MsgResouces_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      MsgResouces_descriptor_,
      MsgResouces::default_instance_,
      MsgResouces_offsets_,
      -1,
      -1,
      -1,
      sizeof(MsgResouces),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MsgResouces, _internal_metadata_),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(MsgResouces, _is_default_instance_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_PB_5fEotq_2eproto3);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      MsgResouces_descriptor_, &MsgResouces::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_PB_5fEotq_2eproto3() {
  delete MsgResouces::default_instance_;
  delete MsgResouces_reflection_;
}

void protobuf_AddDesc_PB_5fEotq_2eproto3() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016PB_Eotq.proto3\022\007PB_Eotq\"4\n\013MsgResouces"
    "\022\013\n\003lck\030\001 \001(\r\022\013\n\003rck\030\002 \001(\r\022\013\n\003val\030\003 \001(\rb"
    "\006proto3", 87);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "PB_Eotq.proto3", &protobuf_RegisterTypes);
  MsgResouces::default_instance_ = new MsgResouces();
  MsgResouces::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_PB_5fEotq_2eproto3);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_PB_5fEotq_2eproto3 {
  StaticDescriptorInitializer_PB_5fEotq_2eproto3() {
    protobuf_AddDesc_PB_5fEotq_2eproto3();
  }
} static_descriptor_initializer_PB_5fEotq_2eproto3_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD;
static void MergeFromFail(int line) {
  GOOGLE_CHECK(false) << __FILE__ << ":" << line;
}

}  // namespace


// ===================================================================

#ifndef _MSC_VER
const int MsgResouces::kLckFieldNumber;
const int MsgResouces::kRckFieldNumber;
const int MsgResouces::kValFieldNumber;
#endif  // !_MSC_VER

MsgResouces::MsgResouces()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:PB_Eotq.MsgResouces)
}

void MsgResouces::InitAsDefaultInstance() {
  _is_default_instance_ = true;
}

MsgResouces::MsgResouces(const MsgResouces& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:PB_Eotq.MsgResouces)
}

void MsgResouces::SharedCtor() {
    _is_default_instance_ = false;
  _cached_size_ = 0;
  lck_ = 0u;
  rck_ = 0u;
  val_ = 0u;
}

MsgResouces::~MsgResouces() {
  // @@protoc_insertion_point(destructor:PB_Eotq.MsgResouces)
  SharedDtor();
}

void MsgResouces::SharedDtor() {
  if (this != default_instance_) {
  }
}

void MsgResouces::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* MsgResouces::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return MsgResouces_descriptor_;
}

const MsgResouces& MsgResouces::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_PB_5fEotq_2eproto3();
  return *default_instance_;
}

MsgResouces* MsgResouces::default_instance_ = NULL;

MsgResouces* MsgResouces::New(::google::protobuf::Arena* arena) const {
  MsgResouces* n = new MsgResouces;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void MsgResouces::Clear() {
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<MsgResouces*>(16)->f)

#define ZR_(first, last) do {\
  ::memset(&first, 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(lck_, val_);

#undef ZR_HELPER_
#undef ZR_

}

bool MsgResouces::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:PB_Eotq.MsgResouces)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional uint32 lck = 1;
      case 1: {
        if (tag == 8) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &lck_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_rck;
        break;
      }

      // optional uint32 rck = 2;
      case 2: {
        if (tag == 16) {
         parse_rck:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &rck_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_val;
        break;
      }

      // optional uint32 val = 3;
      case 3: {
        if (tag == 24) {
         parse_val:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &val_)));

        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:PB_Eotq.MsgResouces)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:PB_Eotq.MsgResouces)
  return false;
#undef DO_
}

void MsgResouces::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:PB_Eotq.MsgResouces)
  // optional uint32 lck = 1;
  if (this->lck() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->lck(), output);
  }

  // optional uint32 rck = 2;
  if (this->rck() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->rck(), output);
  }

  // optional uint32 val = 3;
  if (this->val() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(3, this->val(), output);
  }

  // @@protoc_insertion_point(serialize_end:PB_Eotq.MsgResouces)
}

::google::protobuf::uint8* MsgResouces::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:PB_Eotq.MsgResouces)
  // optional uint32 lck = 1;
  if (this->lck() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->lck(), target);
  }

  // optional uint32 rck = 2;
  if (this->rck() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->rck(), target);
  }

  // optional uint32 val = 3;
  if (this->val() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(3, this->val(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:PB_Eotq.MsgResouces)
  return target;
}

int MsgResouces::ByteSize() const {
  int total_size = 0;

  // optional uint32 lck = 1;
  if (this->lck() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->lck());
  }

  // optional uint32 rck = 2;
  if (this->rck() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->rck());
  }

  // optional uint32 val = 3;
  if (this->val() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::UInt32Size(
        this->val());
  }

  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void MsgResouces::MergeFrom(const ::google::protobuf::Message& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const MsgResouces* source = 
      ::google::protobuf::internal::DynamicCastToGenerated<const MsgResouces>(
          &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void MsgResouces::MergeFrom(const MsgResouces& from) {
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  if (from.lck() != 0) {
    set_lck(from.lck());
  }
  if (from.rck() != 0) {
    set_rck(from.rck());
  }
  if (from.val() != 0) {
    set_val(from.val());
  }
}

void MsgResouces::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MsgResouces::CopyFrom(const MsgResouces& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MsgResouces::IsInitialized() const {

  return true;
}

void MsgResouces::Swap(MsgResouces* other) {
  if (other == this) return;
  InternalSwap(other);
}
void MsgResouces::InternalSwap(MsgResouces* other) {
  std::swap(lck_, other->lck_);
  std::swap(rck_, other->rck_);
  std::swap(val_, other->val_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata MsgResouces::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = MsgResouces_descriptor_;
  metadata.reflection = MsgResouces_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// MsgResouces

// optional uint32 lck = 1;
void MsgResouces::clear_lck() {
  lck_ = 0u;
}
 ::google::protobuf::uint32 MsgResouces::lck() const {
  // @@protoc_insertion_point(field_get:PB_Eotq.MsgResouces.lck)
  return lck_;
}
 void MsgResouces::set_lck(::google::protobuf::uint32 value) {
  
  lck_ = value;
  // @@protoc_insertion_point(field_set:PB_Eotq.MsgResouces.lck)
}

// optional uint32 rck = 2;
void MsgResouces::clear_rck() {
  rck_ = 0u;
}
 ::google::protobuf::uint32 MsgResouces::rck() const {
  // @@protoc_insertion_point(field_get:PB_Eotq.MsgResouces.rck)
  return rck_;
}
 void MsgResouces::set_rck(::google::protobuf::uint32 value) {
  
  rck_ = value;
  // @@protoc_insertion_point(field_set:PB_Eotq.MsgResouces.rck)
}

// optional uint32 val = 3;
void MsgResouces::clear_val() {
  val_ = 0u;
}
 ::google::protobuf::uint32 MsgResouces::val() const {
  // @@protoc_insertion_point(field_get:PB_Eotq.MsgResouces.val)
  return val_;
}
 void MsgResouces::set_val(::google::protobuf::uint32 value) {
  
  val_ = value;
  // @@protoc_insertion_point(field_set:PB_Eotq.MsgResouces.val)
}

#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

}  // namespace PB_Eotq

// @@protoc_insertion_point(global_scope)
