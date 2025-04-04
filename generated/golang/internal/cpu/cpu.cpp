// generated by GoCpp from file '$(ImportDir)/internal/cpu/cpu.go'
#include <complex>
#include <functional>
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <tuple>
#include <vector>

#include "golang/internal/cpu/cpu.h"
#include "gocpp/support.h"

#include "golang/internal/cpu/cpu_x86.h"

namespace golang::cpu
{
    bool DebugOptions;
    
    template<typename T> requires gocpp::GoStruct<T>
    CacheLinePad::operator T()
    {
        T result;
        result._ = this->_;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool CacheLinePad::operator==(const T& ref) const
    {
        if (_ != ref._) return false;
        return true;
    }

    std::ostream& CacheLinePad::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << _;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct CacheLinePad& value)
    {
        return value.PrintTo(os);
    }

    uintptr_t CacheLineSize = CacheLinePadSize;
    struct gocpp_id_0
    {
        CacheLinePad _;
        bool HasAES;
        bool HasADX;
        bool HasAVX;
        bool HasAVX2;
        bool HasAVX512F;
        bool HasAVX512BW;
        bool HasAVX512VL;
        bool HasBMI1;
        bool HasBMI2;
        bool HasERMS;
        bool HasFMA;
        bool HasOSXSAVE;
        bool HasPCLMULQDQ;
        bool HasPOPCNT;
        bool HasRDTSCP;
        bool HasSHA;
        bool HasSSE3;
        bool HasSSSE3;
        bool HasSSE41;
        bool HasSSE42;
        CacheLinePad _;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T()
        {
            T result;
            result._ = this->_;
            result.HasAES = this->HasAES;
            result.HasADX = this->HasADX;
            result.HasAVX = this->HasAVX;
            result.HasAVX2 = this->HasAVX2;
            result.HasAVX512F = this->HasAVX512F;
            result.HasAVX512BW = this->HasAVX512BW;
            result.HasAVX512VL = this->HasAVX512VL;
            result.HasBMI1 = this->HasBMI1;
            result.HasBMI2 = this->HasBMI2;
            result.HasERMS = this->HasERMS;
            result.HasFMA = this->HasFMA;
            result.HasOSXSAVE = this->HasOSXSAVE;
            result.HasPCLMULQDQ = this->HasPCLMULQDQ;
            result.HasPOPCNT = this->HasPOPCNT;
            result.HasRDTSCP = this->HasRDTSCP;
            result.HasSHA = this->HasSHA;
            result.HasSSE3 = this->HasSSE3;
            result.HasSSSE3 = this->HasSSSE3;
            result.HasSSE41 = this->HasSSE41;
            result.HasSSE42 = this->HasSSE42;
            result._ = this->_;
            return result;
        }

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const
        {
            if (_ != ref._) return false;
            if (HasAES != ref.HasAES) return false;
            if (HasADX != ref.HasADX) return false;
            if (HasAVX != ref.HasAVX) return false;
            if (HasAVX2 != ref.HasAVX2) return false;
            if (HasAVX512F != ref.HasAVX512F) return false;
            if (HasAVX512BW != ref.HasAVX512BW) return false;
            if (HasAVX512VL != ref.HasAVX512VL) return false;
            if (HasBMI1 != ref.HasBMI1) return false;
            if (HasBMI2 != ref.HasBMI2) return false;
            if (HasERMS != ref.HasERMS) return false;
            if (HasFMA != ref.HasFMA) return false;
            if (HasOSXSAVE != ref.HasOSXSAVE) return false;
            if (HasPCLMULQDQ != ref.HasPCLMULQDQ) return false;
            if (HasPOPCNT != ref.HasPOPCNT) return false;
            if (HasRDTSCP != ref.HasRDTSCP) return false;
            if (HasSHA != ref.HasSHA) return false;
            if (HasSSE3 != ref.HasSSE3) return false;
            if (HasSSSE3 != ref.HasSSSE3) return false;
            if (HasSSE41 != ref.HasSSE41) return false;
            if (HasSSE42 != ref.HasSSE42) return false;
            if (_ != ref._) return false;
            return true;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << _;
            os << " " << HasAES;
            os << " " << HasADX;
            os << " " << HasAVX;
            os << " " << HasAVX2;
            os << " " << HasAVX512F;
            os << " " << HasAVX512BW;
            os << " " << HasAVX512VL;
            os << " " << HasBMI1;
            os << " " << HasBMI2;
            os << " " << HasERMS;
            os << " " << HasFMA;
            os << " " << HasOSXSAVE;
            os << " " << HasPCLMULQDQ;
            os << " " << HasPOPCNT;
            os << " " << HasRDTSCP;
            os << " " << HasSHA;
            os << " " << HasSSE3;
            os << " " << HasSSSE3;
            os << " " << HasSSE41;
            os << " " << HasSSE42;
            os << " " << _;
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const struct gocpp_id_0& value)
    {
        return value.PrintTo(os);
    }


    gocpp_id_0 X86;
    struct gocpp_id_1
    {
        CacheLinePad _;
        bool HasVFPv4;
        bool HasIDIVA;
        bool HasV7Atomics;
        CacheLinePad _;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T()
        {
            T result;
            result._ = this->_;
            result.HasVFPv4 = this->HasVFPv4;
            result.HasIDIVA = this->HasIDIVA;
            result.HasV7Atomics = this->HasV7Atomics;
            result._ = this->_;
            return result;
        }

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const
        {
            if (_ != ref._) return false;
            if (HasVFPv4 != ref.HasVFPv4) return false;
            if (HasIDIVA != ref.HasIDIVA) return false;
            if (HasV7Atomics != ref.HasV7Atomics) return false;
            if (_ != ref._) return false;
            return true;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << _;
            os << " " << HasVFPv4;
            os << " " << HasIDIVA;
            os << " " << HasV7Atomics;
            os << " " << _;
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const struct gocpp_id_1& value)
    {
        return value.PrintTo(os);
    }


    gocpp_id_1 ARM;
    struct gocpp_id_2
    {
        CacheLinePad _;
        bool HasAES;
        bool HasPMULL;
        bool HasSHA1;
        bool HasSHA2;
        bool HasSHA512;
        bool HasCRC32;
        bool HasATOMICS;
        bool HasCPUID;
        bool IsNeoverse;
        CacheLinePad _;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T()
        {
            T result;
            result._ = this->_;
            result.HasAES = this->HasAES;
            result.HasPMULL = this->HasPMULL;
            result.HasSHA1 = this->HasSHA1;
            result.HasSHA2 = this->HasSHA2;
            result.HasSHA512 = this->HasSHA512;
            result.HasCRC32 = this->HasCRC32;
            result.HasATOMICS = this->HasATOMICS;
            result.HasCPUID = this->HasCPUID;
            result.IsNeoverse = this->IsNeoverse;
            result._ = this->_;
            return result;
        }

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const
        {
            if (_ != ref._) return false;
            if (HasAES != ref.HasAES) return false;
            if (HasPMULL != ref.HasPMULL) return false;
            if (HasSHA1 != ref.HasSHA1) return false;
            if (HasSHA2 != ref.HasSHA2) return false;
            if (HasSHA512 != ref.HasSHA512) return false;
            if (HasCRC32 != ref.HasCRC32) return false;
            if (HasATOMICS != ref.HasATOMICS) return false;
            if (HasCPUID != ref.HasCPUID) return false;
            if (IsNeoverse != ref.IsNeoverse) return false;
            if (_ != ref._) return false;
            return true;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << _;
            os << " " << HasAES;
            os << " " << HasPMULL;
            os << " " << HasSHA1;
            os << " " << HasSHA2;
            os << " " << HasSHA512;
            os << " " << HasCRC32;
            os << " " << HasATOMICS;
            os << " " << HasCPUID;
            os << " " << IsNeoverse;
            os << " " << _;
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const struct gocpp_id_2& value)
    {
        return value.PrintTo(os);
    }


    gocpp_id_2 ARM64;
    struct gocpp_id_3
    {
        CacheLinePad _;
        bool HasMSA;
        CacheLinePad _;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T()
        {
            T result;
            result._ = this->_;
            result.HasMSA = this->HasMSA;
            result._ = this->_;
            return result;
        }

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const
        {
            if (_ != ref._) return false;
            if (HasMSA != ref.HasMSA) return false;
            if (_ != ref._) return false;
            return true;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << _;
            os << " " << HasMSA;
            os << " " << _;
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const struct gocpp_id_3& value)
    {
        return value.PrintTo(os);
    }


    gocpp_id_3 MIPS64X;
    struct gocpp_id_4
    {
        CacheLinePad _;
        bool HasDARN;
        bool HasSCV;
        bool IsPOWER8;
        bool IsPOWER9;
        bool IsPOWER10;
        CacheLinePad _;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T()
        {
            T result;
            result._ = this->_;
            result.HasDARN = this->HasDARN;
            result.HasSCV = this->HasSCV;
            result.IsPOWER8 = this->IsPOWER8;
            result.IsPOWER9 = this->IsPOWER9;
            result.IsPOWER10 = this->IsPOWER10;
            result._ = this->_;
            return result;
        }

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const
        {
            if (_ != ref._) return false;
            if (HasDARN != ref.HasDARN) return false;
            if (HasSCV != ref.HasSCV) return false;
            if (IsPOWER8 != ref.IsPOWER8) return false;
            if (IsPOWER9 != ref.IsPOWER9) return false;
            if (IsPOWER10 != ref.IsPOWER10) return false;
            if (_ != ref._) return false;
            return true;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << _;
            os << " " << HasDARN;
            os << " " << HasSCV;
            os << " " << IsPOWER8;
            os << " " << IsPOWER9;
            os << " " << IsPOWER10;
            os << " " << _;
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const struct gocpp_id_4& value)
    {
        return value.PrintTo(os);
    }


    gocpp_id_4 PPC64;
    struct gocpp_id_5
    {
        CacheLinePad _;
        bool HasZARCH;
        bool HasSTFLE;
        bool HasLDISP;
        bool HasEIMM;
        bool HasDFP;
        bool HasETF3EH;
        bool HasMSA;
        bool HasAES;
        bool HasAESCBC;
        bool HasAESCTR;
        bool HasAESGCM;
        bool HasGHASH;
        bool HasSHA1;
        bool HasSHA256;
        bool HasSHA512;
        bool HasSHA3;
        bool HasVX;
        bool HasVXE;
        bool HasKDSA;
        bool HasECDSA;
        bool HasEDDSA;
        CacheLinePad _;

        using isGoStruct = void;

        template<typename T> requires gocpp::GoStruct<T>
        operator T()
        {
            T result;
            result._ = this->_;
            result.HasZARCH = this->HasZARCH;
            result.HasSTFLE = this->HasSTFLE;
            result.HasLDISP = this->HasLDISP;
            result.HasEIMM = this->HasEIMM;
            result.HasDFP = this->HasDFP;
            result.HasETF3EH = this->HasETF3EH;
            result.HasMSA = this->HasMSA;
            result.HasAES = this->HasAES;
            result.HasAESCBC = this->HasAESCBC;
            result.HasAESCTR = this->HasAESCTR;
            result.HasAESGCM = this->HasAESGCM;
            result.HasGHASH = this->HasGHASH;
            result.HasSHA1 = this->HasSHA1;
            result.HasSHA256 = this->HasSHA256;
            result.HasSHA512 = this->HasSHA512;
            result.HasSHA3 = this->HasSHA3;
            result.HasVX = this->HasVX;
            result.HasVXE = this->HasVXE;
            result.HasKDSA = this->HasKDSA;
            result.HasECDSA = this->HasECDSA;
            result.HasEDDSA = this->HasEDDSA;
            result._ = this->_;
            return result;
        }

        template<typename T> requires gocpp::GoStruct<T>
        bool operator==(const T& ref) const
        {
            if (_ != ref._) return false;
            if (HasZARCH != ref.HasZARCH) return false;
            if (HasSTFLE != ref.HasSTFLE) return false;
            if (HasLDISP != ref.HasLDISP) return false;
            if (HasEIMM != ref.HasEIMM) return false;
            if (HasDFP != ref.HasDFP) return false;
            if (HasETF3EH != ref.HasETF3EH) return false;
            if (HasMSA != ref.HasMSA) return false;
            if (HasAES != ref.HasAES) return false;
            if (HasAESCBC != ref.HasAESCBC) return false;
            if (HasAESCTR != ref.HasAESCTR) return false;
            if (HasAESGCM != ref.HasAESGCM) return false;
            if (HasGHASH != ref.HasGHASH) return false;
            if (HasSHA1 != ref.HasSHA1) return false;
            if (HasSHA256 != ref.HasSHA256) return false;
            if (HasSHA512 != ref.HasSHA512) return false;
            if (HasSHA3 != ref.HasSHA3) return false;
            if (HasVX != ref.HasVX) return false;
            if (HasVXE != ref.HasVXE) return false;
            if (HasKDSA != ref.HasKDSA) return false;
            if (HasECDSA != ref.HasECDSA) return false;
            if (HasEDDSA != ref.HasEDDSA) return false;
            if (_ != ref._) return false;
            return true;
        }

        std::ostream& PrintTo(std::ostream& os) const
        {
            os << '{';
            os << "" << _;
            os << " " << HasZARCH;
            os << " " << HasSTFLE;
            os << " " << HasLDISP;
            os << " " << HasEIMM;
            os << " " << HasDFP;
            os << " " << HasETF3EH;
            os << " " << HasMSA;
            os << " " << HasAES;
            os << " " << HasAESCBC;
            os << " " << HasAESCTR;
            os << " " << HasAESGCM;
            os << " " << HasGHASH;
            os << " " << HasSHA1;
            os << " " << HasSHA256;
            os << " " << HasSHA512;
            os << " " << HasSHA3;
            os << " " << HasVX;
            os << " " << HasVXE;
            os << " " << HasKDSA;
            os << " " << HasECDSA;
            os << " " << HasEDDSA;
            os << " " << _;
            os << '}';
            return os;
        }
    };

    std::ostream& operator<<(std::ostream& os, const struct gocpp_id_5& value)
    {
        return value.PrintTo(os);
    }


    gocpp_id_5 S390X;
    void Initialize(std::string env)
    {
        doinit();
        processOptions(env);
    }

    gocpp::slice<option> options;
    
    template<typename T> requires gocpp::GoStruct<T>
    option::operator T()
    {
        T result;
        result.Name = this->Name;
        result.Feature = this->Feature;
        result.Specified = this->Specified;
        result.Enable = this->Enable;
        return result;
    }

    template<typename T> requires gocpp::GoStruct<T>
    bool option::operator==(const T& ref) const
    {
        if (Name != ref.Name) return false;
        if (Feature != ref.Feature) return false;
        if (Specified != ref.Specified) return false;
        if (Enable != ref.Enable) return false;
        return true;
    }

    std::ostream& option::PrintTo(std::ostream& os) const
    {
        os << '{';
        os << "" << Name;
        os << " " << Feature;
        os << " " << Specified;
        os << " " << Enable;
        os << '}';
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const struct option& value)
    {
        return value.PrintTo(os);
    }

    void processOptions(std::string env)
    {
        field:
        for(; env != ""; )
        {
            auto field = "";
            auto i = indexByte(env, ',');
            if(i < 0)
            {
                std::tie(field, env) = std::tuple{env, ""};
            }
            else
            {
                std::tie(field, env) = std::tuple{env.make_slice(0, i), env.make_slice(i + 1)};
            }
            if(len(field) < 4 || field.make_slice(0, 4) != "cpu.")
            {
                continue;
            }
            i = indexByte(field, '=');
            if(i < 0)
            {
                print("GODEBUG: no value specified for \"", field, "\"\n");
                continue;
            }
            auto [key, value] = std::tuple{field.make_slice(4, i), field.make_slice(i + 1)};
            bool enable = {};
            //Go switch emulation
            {
                auto condition = value;
                int conditionId = -1;
                if(condition == "on") { conditionId = 0; }
                else if(condition == "off") { conditionId = 1; }
                switch(conditionId)
                {
                    case 0:
                        enable = true;
                        break;
                    case 1:
                        enable = false;
                        break;
                    default:
                        print("GODEBUG: value \"", value, "\" not supported for cpu option \"", key, "\"\n");
                        goto field_continue;
                        break;
                }
            }
            if(key == "all")
            {
                for(auto [i, gocpp_ignored] : options)
                {
                    options[i].Specified = true;
                    options[i].Enable = enable;
                }
                goto field_continue;
            }
            for(auto [i, gocpp_ignored] : options)
            {
                if(options[i].Name == key)
                {
                    options[i].Specified = true;
                    options[i].Enable = enable;
                    goto field_continue;
                }
            }
            print("GODEBUG: unknown cpu feature \"", key, "\"\n");
            if(false) {
            field_continue:
                continue;
            field_break:
                break;
            }
        }
        for(auto [_, o] : options)
        {
            if(! o.Specified)
            {
                continue;
            }
            if(o.Enable && ! *o.Feature)
            {
                print("GODEBUG: can not enable \"", o.Name, "\", missing CPU support\n");
                continue;
            }
            *o.Feature = o.Enable;
        }
    }

    int indexByte(std::string s, unsigned char c)
    {
        for(auto i = 0; i < len(s); i++)
        {
            if(s[i] == c)
            {
                return i;
            }
        }
        return - 1;
    }

}

