

#include "common.hlsl"


Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
SamplerState g_SamplerState : register(s0);

static const float PI = 3.141592;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    //視線ベクトル
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    
    //法線ベクトル
    float3 normal = normalize(In.Normal.xyz);
    
    //反射
    float3 refColor;
    {
    
        //反射ベクトル
        float3 refv = reflect(eyev.xyz, normal);
        refv = normalize(refv);
    
        //環境マッピングテクスチャ座標(スフィアマップ)
        //float2 envTexCoord;
        //envTexCoord.x = refv.x * 0.5 + 0.5;
        //envTexCoord.y = -refv.y * 0.5 + 0.5;
    
        //環境マッピングテクスチャ座標(パノラマ)
        float2 envTexCoord;
        envTexCoord.x = atan2(refv.x, refv.z) / (PI * 2);
        envTexCoord.y = acos(refv.y) / PI;
    
        //環境マッピング
        refColor = g_TextureEnv.Sample(g_SamplerState, envTexCoord);
    }
    
    //屈折
    float3 refrColor;
    {
        //屈折ベクトル
        float3 refrv = refract(eyev.x, normal, 1.0 / 1.5);
        refrv = normalize(refrv);
    
        //屈折マッピングテクスチャ座標(パノラマ)
        float2 envTexCoord;
        envTexCoord.x = atan2(refrv.x, refrv.z) / (PI * 2);
        envTexCoord.y = acos(refrv.y) / PI;
    
        //屈折マッピング
        refrColor = g_TextureEnv.Sample(g_SamplerState, envTexCoord);
    }
    
    //フレネル反射率(Schlick近似式)
    float f0 = 0.04;
    float d = saturate(dot(-eyev, normal));
    float fresnel = f0 + (1.0 - f0) * pow((1.0 - d), 2.0);
    
    outDiffuse.rgb = lerp(refrColor, refColor, fresnel);
    outDiffuse.a = 1.0;

}

