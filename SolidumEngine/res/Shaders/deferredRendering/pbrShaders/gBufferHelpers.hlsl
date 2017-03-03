PS_GBUFFER_OUT PackGBuffer(Material mat)
{
  PS_GBUFFER_OUT output;

  output.Color = float4(mat.diffuseColor.rgb, mat.roughness);

  output.Normal = float4(mat.normal.xyz, mat.metallic);

  output.GlowMap = float4(mat.glowColor * mat.glowIntensity, 1.0f);

  return output;
};

GBUFFER_DATA UnpackGBuffer(int2 location)
{
  GBUFFER_DATA output;

  int3 loc3 = int3(location, 0);

  //sample the base color
  float4 color = ColorTexture.Load(loc3);

  //set the base color
  output.diffuseColor.rgb = color.rgb;

  //sample the normal data (normal and depth)
  float4 NormalData = NormalTexture.Load(loc3);

  //convert to normal range then normalize
  output.normal = normalize(NormalData.xyz);

  //sample the spec power
  output.roughness = color.a;
  output.metallic = NormalData.w;

  //sample the depth in ndc space and leave to converting depth to different space by shaders
  output.ndcDepthZ = DepthTexture.Load(loc3).r;

  return output;
};