// generated by GoCpp from file '$(ImportDir)/internal/abi/type.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/abi/type.h"
#include "gocpp/support.h"

#include "golang/unsafe/unsafe.h"

namespace golang::abi
{
    
    template<typename T> requires gocpp::GoStruct<T>
    Type::operator T()
    {
        T result;
        result.Size_ = this->Size_;
        result.PtrBytes = this->PtrBytes;
        result.Hash = this->Hash;
        result.TFlag = this->TFlag;
        result.Align_ = this->Align_;
        result.FieldAlign_ = this->FieldAlign_;
        result.Kind_ = this->Kind_;
        result.Equal = this->Equal;
        result.GCData = this->GCData;
        result.Str = this->Str;
        result.PtrToThis = this->PtrToThis;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Type::operator==(const T& ref) const
    {
        if (Size_ != ref.Size_) return false;
        if (PtrBytes != ref.PtrBytes) return false;
        if (Hash != ref.Hash) return false;
        if (TFlag != ref.TFlag) return false;
        if (Align_ != ref.Align_) return false;
        if (FieldAlign_ != ref.FieldAlign_) return false;
        if (Kind_ != ref.Kind_) return false;
        if (Equal != ref.Equal) return false;
        if (GCData != ref.GCData) return false;
        if (Str != ref.Str) return false;
        if (PtrToThis != ref.PtrToThis) return false;
        return true;
    }

    std::ostream& Type::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Size_;
        os << " " << PtrBytes;
        os << " " << Hash;
        os << " " << TFlag;
        os << " " << Align_;
        os << " " << FieldAlign_;
        os << " " << Kind_;
        os << " " << Equal;
        os << " " << GCData;
        os << " " << Str;
        os << " " << PtrToThis;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Type& value)
    {
        return value.PrintTo(os);
    }

    std::string String(Kind k)
    {
        if(int(k) < len(kindNames))
        {
            return kindNames[k];
        }
        return kindNames[0];
    }

    gocpp::slice<std::string> kindNames = gocpp::Init<gocpp::slice<std::string>>([](gocpp::slice<std::string>& x) { x.Invalid = "invalid"; x.Bool = "bool"; x.Int = "int"; x.Int8 = "int8"; x.Int16 = "int16"; x.Int32 = "int32"; x.Int64 = "int64"; x.Uint = "uint"; x.Uint8 = "uint8"; x.Uint16 = "uint16"; x.Uint32 = "uint32"; x.Uint64 = "uint64"; x.Uintptr = "uintptr"; x.Float32 = "float32"; x.Float64 = "float64"; x.Complex64 = "complex64"; x.Complex128 = "complex128"; x.Array = "array"; x.Chan = "chan"; x.Func = "func"; x.Interface = "interface"; x.Map = "map"; x.Pointer = "ptr"; x.Slice = "slice"; x.String = "string"; x.Struct = "struct"; x.UnsafePointer = "unsafe.Pointer"; });
    Kind Kind(struct Type* t)
    {
        return Kind(t->Kind_ & KindMask);
    }

    bool HasName(struct Type* t)
    {
        return t->TFlag & TFlagNamed != 0;
    }

    bool Pointers(struct Type* t)
    {
        return t->PtrBytes != 0;
    }

    bool IfaceIndir(struct Type* t)
    {
        return t->Kind_ & KindDirectIface == 0;
    }

    bool IsDirectIface(struct Type* t)
    {
        return t->Kind_ & KindDirectIface != 0;
    }

    gocpp::slice<unsigned char> GcSlice(struct Type* t, uintptr_t begin, uintptr_t end)
    {
        return unsafe::Slice(t->GCData, int(end)).make_slice(begin);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    Method::operator T()
    {
        T result;
        result.Name = this->Name;
        result.Mtyp = this->Mtyp;
        result.Ifn = this->Ifn;
        result.Tfn = this->Tfn;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Method::operator==(const T& ref) const
    {
        if (Name != ref.Name) return false;
        if (Mtyp != ref.Mtyp) return false;
        if (Ifn != ref.Ifn) return false;
        if (Tfn != ref.Tfn) return false;
        return true;
    }

    std::ostream& Method::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Name;
        os << " " << Mtyp;
        os << " " << Ifn;
        os << " " << Tfn;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Method& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    UncommonType::operator T()
    {
        T result;
        result.PkgPath = this->PkgPath;
        result.Mcount = this->Mcount;
        result.Xcount = this->Xcount;
        result.Moff = this->Moff;
        result._ = this->_;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool UncommonType::operator==(const T& ref) const
    {
        if (PkgPath != ref.PkgPath) return false;
        if (Mcount != ref.Mcount) return false;
        if (Xcount != ref.Xcount) return false;
        if (Moff != ref.Moff) return false;
        if (_ != ref._) return false;
        return true;
    }

    std::ostream& UncommonType::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << PkgPath;
        os << " " << Mcount;
        os << " " << Xcount;
        os << " " << Moff;
        os << " " << _;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct UncommonType& value)
    {
        return value.PrintTo(os);
    }

    gocpp::slice<Method> Methods(struct UncommonType* t)
    {
        if(t->Mcount == 0)
        {
            return nullptr;
        }
        return (gocpp::array<Method, 1 << 16>*)(addChecked(unsafe::Pointer(t), uintptr_t(t->Moff), "t.mcount > 0")).make_slice(, t->Mcount, t->Mcount);
    }

    gocpp::slice<Method> ExportedMethods(struct UncommonType* t)
    {
        if(t->Xcount == 0)
        {
            return nullptr;
        }
        return (gocpp::array<Method, 1 << 16>*)(addChecked(unsafe::Pointer(t), uintptr_t(t->Moff), "t.xcount > 0")).make_slice(, t->Xcount, t->Xcount);
    }

    unsafe::Pointer addChecked(unsafe::Pointer p, uintptr_t x, std::string whySafe)
    {
        return unsafe::Pointer(uintptr_t(p) + x);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    Imethod::operator T()
    {
        T result;
        result.Name = this->Name;
        result.Typ = this->Typ;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Imethod::operator==(const T& ref) const
    {
        if (Name != ref.Name) return false;
        if (Typ != ref.Typ) return false;
        return true;
    }

    std::ostream& Imethod::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Name;
        os << " " << Typ;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Imethod& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    ArrayType::operator T()
    {
        T result;
        result.Elem = this->Elem;
        result.Slice = this->Slice;
        result.Len = this->Len;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool ArrayType::operator==(const T& ref) const
    {
        if (Elem != ref.Elem) return false;
        if (Slice != ref.Slice) return false;
        if (Len != ref.Len) return false;
        return true;
    }

    std::ostream& ArrayType::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Elem;
        os << " " << Slice;
        os << " " << Len;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct ArrayType& value)
    {
        return value.PrintTo(os);
    }

    int Len(struct Type* t)
    {
        if(Kind(gocpp::recv(t)) == Array)
        {
            return int((ArrayType*)(unsafe::Pointer(t))->Len);
        }
        return 0;
    }

    Type* Common(struct Type* t)
    {
        return t;
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    ChanType::operator T()
    {
        T result;
        result.Elem = this->Elem;
        result.Dir = this->Dir;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool ChanType::operator==(const T& ref) const
    {
        if (Elem != ref.Elem) return false;
        if (Dir != ref.Dir) return false;
        return true;
    }

    std::ostream& ChanType::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Elem;
        os << " " << Dir;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct ChanType& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    structTypeUncommon::operator T()
    {
        T result;
        result.u = this->u;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool structTypeUncommon::operator==(const T& ref) const
    {
        if (u != ref.u) return false;
        return true;
    }

    std::ostream& structTypeUncommon::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << u;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct structTypeUncommon& value)
    {
        return value.PrintTo(os);
    }

    ChanDir ChanDir(struct Type* t)
    {
        if(Kind(gocpp::recv(t)) == Chan)
        {
            auto ch = (ChanType*)(unsafe::Pointer(t));
            return ch->Dir;
        }
        return InvalidDir;
    }

    UncommonType* Uncommon(struct Type* t)
    {
        if(t->TFlag & TFlagUncommon == 0)
        {
            return nullptr;
        }
        //Go switch emulation
        {
            auto condition = Kind(gocpp::recv(t));
            int conditionId = -1;
            if(condition == Struct) { conditionId = 0; }
            else if(condition == Pointer) { conditionId = 1; }
            else if(condition == Func) { conditionId = 2; }
            else if(condition == Slice) { conditionId = 3; }
            else if(condition == Array) { conditionId = 4; }
            else if(condition == Chan) { conditionId = 5; }
            else if(condition == Map) { conditionId = 6; }
            else if(condition == Interface) { conditionId = 7; }
            switch(conditionId)
            {
                case 0:
                    return & (structTypeUncommon*)(unsafe::Pointer(t))->u;
                    break;
                case 1:
                    
                    template<typename T> requires gocpp::GoStruct<T>
                    u::operator T()
                    {
                        T result;
                        result.u = this->u;
                        return result;
                    }

                    template<typename T> requires gocpp::GoStruct<T>
                    bool u::operator==(const T& ref) const
                    {
                        if (u != ref.u) return false;
                        return true;
                    }

                    std::ostream& u::PrintTo(std::ostream& os) const
                    {
                        os << '{';
                        os << "" << u;
                        os << '}';
                        return os;
                    }

                    std::ostream& operator<<(std::ostream& os, const struct u& value)
                    {
                        return value.PrintTo(os);
                    }

                    return & (u*)(unsafe::Pointer(t))->u;
                    break;
                case 2:
                    
                    template<typename T> requires gocpp::GoStruct<T>
                    u::operator T()
                    {
                        T result;
                        result.u = this->u;
                        return result;
                    }

                    template<typename T> requires gocpp::GoStruct<T>
                    bool u::operator==(const T& ref) const
                    {
                        if (u != ref.u) return false;
                        return true;
                    }

                    std::ostream& u::PrintTo(std::ostream& os) const
                    {
                        os << '{';
                        os << "" << u;
                        os << '}';
                        return os;
                    }

                    std::ostream& operator<<(std::ostream& os, const struct u& value)
                    {
                        return value.PrintTo(os);
                    }

                    return & (u*)(unsafe::Pointer(t))->u;
                    break;
                case 3:
                    
                    template<typename T> requires gocpp::GoStruct<T>
                    u::operator T()
                    {
                        T result;
                        result.u = this->u;
                        return result;
                    }

                    template<typename T> requires gocpp::GoStruct<T>
                    bool u::operator==(const T& ref) const
                    {
                        if (u != ref.u) return false;
                        return true;
                    }

                    std::ostream& u::PrintTo(std::ostream& os) const
                    {
                        os << '{';
                        os << "" << u;
                        os << '}';
                        return os;
                    }

                    std::ostream& operator<<(std::ostream& os, const struct u& value)
                    {
                        return value.PrintTo(os);
                    }

                    return & (u*)(unsafe::Pointer(t))->u;
                    break;
                case 4:
                    
                    template<typename T> requires gocpp::GoStruct<T>
                    u::operator T()
                    {
                        T result;
                        result.u = this->u;
                        return result;
                    }

                    template<typename T> requires gocpp::GoStruct<T>
                    bool u::operator==(const T& ref) const
                    {
                        if (u != ref.u) return false;
                        return true;
                    }

                    std::ostream& u::PrintTo(std::ostream& os) const
                    {
                        os << '{';
                        os << "" << u;
                        os << '}';
                        return os;
                    }

                    std::ostream& operator<<(std::ostream& os, const struct u& value)
                    {
                        return value.PrintTo(os);
                    }

                    return & (u*)(unsafe::Pointer(t))->u;
                    break;
                case 5:
                    
                    template<typename T> requires gocpp::GoStruct<T>
                    u::operator T()
                    {
                        T result;
                        result.u = this->u;
                        return result;
                    }

                    template<typename T> requires gocpp::GoStruct<T>
                    bool u::operator==(const T& ref) const
                    {
                        if (u != ref.u) return false;
                        return true;
                    }

                    std::ostream& u::PrintTo(std::ostream& os) const
                    {
                        os << '{';
                        os << "" << u;
                        os << '}';
                        return os;
                    }

                    std::ostream& operator<<(std::ostream& os, const struct u& value)
                    {
                        return value.PrintTo(os);
                    }

                    return & (u*)(unsafe::Pointer(t))->u;
                    break;
                case 6:
                    
                    template<typename T> requires gocpp::GoStruct<T>
                    u::operator T()
                    {
                        T result;
                        result.u = this->u;
                        return result;
                    }

                    template<typename T> requires gocpp::GoStruct<T>
                    bool u::operator==(const T& ref) const
                    {
                        if (u != ref.u) return false;
                        return true;
                    }

                    std::ostream& u::PrintTo(std::ostream& os) const
                    {
                        os << '{';
                        os << "" << u;
                        os << '}';
                        return os;
                    }

                    std::ostream& operator<<(std::ostream& os, const struct u& value)
                    {
                        return value.PrintTo(os);
                    }

                    return & (u*)(unsafe::Pointer(t))->u;
                    break;
                case 7:
                    
                    template<typename T> requires gocpp::GoStruct<T>
                    u::operator T()
                    {
                        T result;
                        result.u = this->u;
                        return result;
                    }

                    template<typename T> requires gocpp::GoStruct<T>
                    bool u::operator==(const T& ref) const
                    {
                        if (u != ref.u) return false;
                        return true;
                    }

                    std::ostream& u::PrintTo(std::ostream& os) const
                    {
                        os << '{';
                        os << "" << u;
                        os << '}';
                        return os;
                    }

                    std::ostream& operator<<(std::ostream& os, const struct u& value)
                    {
                        return value.PrintTo(os);
                    }

                    return & (u*)(unsafe::Pointer(t))->u;
                    break;
                default:
                    
                    template<typename T> requires gocpp::GoStruct<T>
                    u::operator T()
                    {
                        T result;
                        result.u = this->u;
                        return result;
                    }

                    template<typename T> requires gocpp::GoStruct<T>
                    bool u::operator==(const T& ref) const
                    {
                        if (u != ref.u) return false;
                        return true;
                    }

                    std::ostream& u::PrintTo(std::ostream& os) const
                    {
                        os << '{';
                        os << "" << u;
                        os << '}';
                        return os;
                    }

                    std::ostream& operator<<(std::ostream& os, const struct u& value)
                    {
                        return value.PrintTo(os);
                    }

                    return & (u*)(unsafe::Pointer(t))->u;
                    break;
            }
        }
    }

    Type* Elem(struct Type* t)
    {
        //Go switch emulation
        {
            auto condition = Kind(gocpp::recv(t));
            int conditionId = -1;
            if(condition == Array) { conditionId = 0; }
            else if(condition == Chan) { conditionId = 1; }
            else if(condition == Map) { conditionId = 2; }
            else if(condition == Pointer) { conditionId = 3; }
            else if(condition == Slice) { conditionId = 4; }
            switch(conditionId)
            {
                case 0:
                    auto tt = (ArrayType*)(unsafe::Pointer(t));
                    return tt->Elem;
                    break;
                case 1:
                    auto tt = (ChanType*)(unsafe::Pointer(t));
                    return tt->Elem;
                    break;
                case 2:
                    auto tt = (MapType*)(unsafe::Pointer(t));
                    return tt->Elem;
                    break;
                case 3:
                    auto tt = (PtrType*)(unsafe::Pointer(t));
                    return tt->Elem;
                    break;
                case 4:
                    auto tt = (SliceType*)(unsafe::Pointer(t));
                    return tt->Elem;
                    break;
            }
        }
        return nullptr;
    }

    StructType* StructType(struct Type* t)
    {
        if(Kind(gocpp::recv(t)) != Struct)
        {
            return nullptr;
        }
        return (StructType*)(unsafe::Pointer(t));
    }

    MapType* MapType(struct Type* t)
    {
        if(Kind(gocpp::recv(t)) != Map)
        {
            return nullptr;
        }
        return (MapType*)(unsafe::Pointer(t));
    }

    ArrayType* ArrayType(struct Type* t)
    {
        if(Kind(gocpp::recv(t)) != Array)
        {
            return nullptr;
        }
        return (ArrayType*)(unsafe::Pointer(t));
    }

    FuncType* FuncType(struct Type* t)
    {
        if(Kind(gocpp::recv(t)) != Func)
        {
            return nullptr;
        }
        return (FuncType*)(unsafe::Pointer(t));
    }

    InterfaceType* InterfaceType(struct Type* t)
    {
        if(Kind(gocpp::recv(t)) != Interface)
        {
            return nullptr;
        }
        return (InterfaceType*)(unsafe::Pointer(t));
    }

    uintptr_t Size(struct Type* t)
    {
        return t->Size_;
    }

    int Align(struct Type* t)
    {
        return int(t->Align_);
    }

    int FieldAlign(struct Type* t)
    {
        return int(t->FieldAlign_);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    InterfaceType::operator T()
    {
        T result;
        result.PkgPath = this->PkgPath;
        result.Methods = this->Methods;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool InterfaceType::operator==(const T& ref) const
    {
        if (PkgPath != ref.PkgPath) return false;
        if (Methods != ref.Methods) return false;
        return true;
    }

    std::ostream& InterfaceType::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << PkgPath;
        os << " " << Methods;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct InterfaceType& value)
    {
        return value.PrintTo(os);
    }

    gocpp::slice<Method> ExportedMethods(struct Type* t)
    {
        auto ut = Uncommon(gocpp::recv(t));
        if(ut == nullptr)
        {
            return nullptr;
        }
        return ExportedMethods(gocpp::recv(ut));
    }

    int NumMethod(struct Type* t)
    {
        if(Kind(gocpp::recv(t)) == Interface)
        {
            auto tt = (InterfaceType*)(unsafe::Pointer(t));
            return NumMethod(gocpp::recv(tt));
        }
        return len(ExportedMethods(gocpp::recv(t)));
    }

    int NumMethod(struct InterfaceType* t)
    {
        return len(t->Methods);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    MapType::operator T()
    {
        T result;
        result.Key = this->Key;
        result.Elem = this->Elem;
        result.Bucket = this->Bucket;
        result.Hasher = this->Hasher;
        result.KeySize = this->KeySize;
        result.ValueSize = this->ValueSize;
        result.BucketSize = this->BucketSize;
        result.Flags = this->Flags;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool MapType::operator==(const T& ref) const
    {
        if (Key != ref.Key) return false;
        if (Elem != ref.Elem) return false;
        if (Bucket != ref.Bucket) return false;
        if (Hasher != ref.Hasher) return false;
        if (KeySize != ref.KeySize) return false;
        if (ValueSize != ref.ValueSize) return false;
        if (BucketSize != ref.BucketSize) return false;
        if (Flags != ref.Flags) return false;
        return true;
    }

    std::ostream& MapType::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Key;
        os << " " << Elem;
        os << " " << Bucket;
        os << " " << Hasher;
        os << " " << KeySize;
        os << " " << ValueSize;
        os << " " << BucketSize;
        os << " " << Flags;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct MapType& value)
    {
        return value.PrintTo(os);
    }

    bool IndirectKey(struct MapType* mt)
    {
        return mt->Flags & 1 != 0;
    }

    bool IndirectElem(struct MapType* mt)
    {
        return mt->Flags & 2 != 0;
    }

    bool ReflexiveKey(struct MapType* mt)
    {
        return mt->Flags & 4 != 0;
    }

    bool NeedKeyUpdate(struct MapType* mt)
    {
        return mt->Flags & 8 != 0;
    }

    bool HashMightPanic(struct MapType* mt)
    {
        return mt->Flags & 16 != 0;
    }

    Type* Key(struct Type* t)
    {
        if(Kind(gocpp::recv(t)) == Map)
        {
            return (MapType*)(unsafe::Pointer(t))->Key;
        }
        return nullptr;
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    SliceType::operator T()
    {
        T result;
        result.Elem = this->Elem;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool SliceType::operator==(const T& ref) const
    {
        if (Elem != ref.Elem) return false;
        return true;
    }

    std::ostream& SliceType::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Elem;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct SliceType& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    FuncType::operator T()
    {
        T result;
        result.InCount = this->InCount;
        result.OutCount = this->OutCount;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool FuncType::operator==(const T& ref) const
    {
        if (InCount != ref.InCount) return false;
        if (OutCount != ref.OutCount) return false;
        return true;
    }

    std::ostream& FuncType::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << InCount;
        os << " " << OutCount;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct FuncType& value)
    {
        return value.PrintTo(os);
    }

    Type* In(struct FuncType* t, int i)
    {
        return InSlice(gocpp::recv(t))[i];
    }

    int NumIn(struct FuncType* t)
    {
        return int(t->InCount);
    }

    int NumOut(struct FuncType* t)
    {
        return int(t->OutCount & ((1 << 15) - 1));
    }

    Type* Out(struct FuncType* t, int i)
    {
        return (OutSlice(gocpp::recv(t))[i]);
    }

    gocpp::slice<Type*> InSlice(struct FuncType* t)
    {
        auto uadd = gocpp::Sizeof<FuncType>();
        if(t->TFlag & TFlagUncommon != 0)
        {
            uadd += gocpp::Sizeof<UncommonType>();
        }
        if(t->InCount == 0)
        {
            return nullptr;
        }
        return (gocpp::array<Type*, 1 << 16>*)(addChecked(unsafe::Pointer(t), uadd, "t.inCount > 0")).make_slice(, t->InCount, t->InCount);
    }

    gocpp::slice<Type*> OutSlice(struct FuncType* t)
    {
        auto outCount = uint16_t(NumOut(gocpp::recv(t)));
        if(outCount == 0)
        {
            return nullptr;
        }
        auto uadd = gocpp::Sizeof<FuncType>();
        if(t->TFlag & TFlagUncommon != 0)
        {
            uadd += gocpp::Sizeof<UncommonType>();
        }
        return (gocpp::array<Type*, 1 << 17>*)(addChecked(unsafe::Pointer(t), uadd, "outCount > 0")).make_slice(t->InCount, t->InCount + outCount, t->InCount + outCount);
    }

    bool IsVariadic(struct FuncType* t)
    {
        return t->OutCount & (1 << 15) != 0;
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    PtrType::operator T()
    {
        T result;
        result.Elem = this->Elem;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool PtrType::operator==(const T& ref) const
    {
        if (Elem != ref.Elem) return false;
        return true;
    }

    std::ostream& PtrType::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Elem;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct PtrType& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    StructField::operator T()
    {
        T result;
        result.Name = this->Name;
        result.Typ = this->Typ;
        result.Offset = this->Offset;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool StructField::operator==(const T& ref) const
    {
        if (Name != ref.Name) return false;
        if (Typ != ref.Typ) return false;
        if (Offset != ref.Offset) return false;
        return true;
    }

    std::ostream& StructField::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Name;
        os << " " << Typ;
        os << " " << Offset;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct StructField& value)
    {
        return value.PrintTo(os);
    }

    bool Embedded(struct StructField* f)
    {
        return IsEmbedded(gocpp::recv(f->Name));
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    StructType::operator T()
    {
        T result;
        result.PkgPath = this->PkgPath;
        result.Fields = this->Fields;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool StructType::operator==(const T& ref) const
    {
        if (PkgPath != ref.PkgPath) return false;
        if (Fields != ref.Fields) return false;
        return true;
    }

    std::ostream& StructType::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << PkgPath;
        os << " " << Fields;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct StructType& value)
    {
        return value.PrintTo(os);
    }

    
    template<typename T> requires gocpp::GoStruct<T>
    Name::operator T()
    {
        T result;
        result.Bytes = this->Bytes;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool Name::operator==(const T& ref) const
    {
        if (Bytes != ref.Bytes) return false;
        return true;
    }

    std::ostream& Name::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Bytes;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct Name& value)
    {
        return value.PrintTo(os);
    }

    unsigned char* DataChecked(struct Name n, int off, std::string whySafe)
    {
        return (unsigned char*)(addChecked(unsafe::Pointer(n.Bytes), uintptr_t(off), whySafe));
    }

    unsigned char* Data(struct Name n, int off)
    {
        return (unsigned char*)(addChecked(unsafe::Pointer(n.Bytes), uintptr_t(off), "the runtime doesn't need to give you a reason"));
    }

    bool IsExported(struct Name n)
    {
        return (*n.Bytes) & (1 << 0) != 0;
    }

    bool HasTag(struct Name n)
    {
        return (*n.Bytes) & (1 << 1) != 0;
    }

    bool IsEmbedded(struct Name n)
    {
        return (*n.Bytes) & (1 << 3) != 0;
    }

    std::tuple<int, int> ReadVarint(struct Name n, int off)
    {
        auto v = 0;
        for(auto i = 0; ; i++)
        {
            auto x = *DataChecked(gocpp::recv(n), off + i, "read varint");
            v += int(x & 0x7f) << (7 * i);
            if(x & 0x80 == 0)
            {
                return {i + 1, v};
            }
        }
    }

    bool IsBlank(struct Name n)
    {
        if(n.Bytes == nullptr)
        {
            return false;
        }
        auto [gocpp_id_1, l] = ReadVarint(gocpp::recv(n), 1);
        return l == 1 && *Data(gocpp::recv(n), 2) == '_';
    }

    int writeVarint(gocpp::slice<unsigned char> buf, int n)
    {
        for(auto i = 0; ; i++)
        {
            auto b = unsigned char(n & 0x7f);
            n >>= 7;
            if(n == 0)
            {
                buf[i] = b;
                return i + 1;
            }
            buf[i] = b | 0x80;
        }
    }

    std::string Name(struct Name n)
    {
        if(n.Bytes == nullptr)
        {
            return "";
        }
        auto [i, l] = ReadVarint(gocpp::recv(n), 1);
        return unsafe::String(DataChecked(gocpp::recv(n), 1 + i, "non-empty string"), l);
    }

    std::string Tag(struct Name n)
    {
        if(! HasTag(gocpp::recv(n)))
        {
            return "";
        }
        auto [i, l] = ReadVarint(gocpp::recv(n), 1);
        auto [i2, l2] = ReadVarint(gocpp::recv(n), 1 + i + l);
        return unsafe::String(DataChecked(gocpp::recv(n), 1 + i + l + i2, "non-empty string"), l2);
    }

    Name NewName(std::string n, std::string tag, bool exported, bool embedded)
    {
        if(len(n) >= (1 << 29))
        {
            gocpp::panic("abi.NewName: name too long: " + n.make_slice(0, 1024) + "...");
        }
        if(len(tag) >= (1 << 29))
        {
            gocpp::panic("abi.NewName: tag too long: " + tag.make_slice(0, 1024) + "...");
        }
        gocpp::array<unsigned char, 10> nameLen = {};
        gocpp::array<unsigned char, 10> tagLen = {};
        auto nameLenLen = writeVarint(nameLen.make_slice(0, ), len(n));
        auto tagLenLen = writeVarint(tagLen.make_slice(0, ), len(tag));
        unsigned char bits = {};
        auto l = 1 + nameLenLen + len(n);
        if(exported)
        {
            bits |= 1 << 0;
        }
        if(len(tag) > 0)
        {
            l += tagLenLen + len(tag);
            bits |= 1 << 1;
        }
        if(embedded)
        {
            bits |= 1 << 3;
        }
        auto b = gocpp::make(gocpp::Tag<gocpp::slice<unsigned char>>(), l);
        b[0] = bits;
        copy(b.make_slice(1), nameLen.make_slice(0, nameLenLen));
        copy(b.make_slice(1 + nameLenLen), n);
        if(len(tag) > 0)
        {
            auto tb = b.make_slice(1 + nameLenLen + len(n));
            copy(tb, tagLen.make_slice(0, tagLenLen));
            copy(tb.make_slice(tagLenLen), tag);
        }
        return gocpp::Init<Name>([](Name& x) { x.Bytes = & b[0]; });
    }

}

