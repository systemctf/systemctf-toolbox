#include <openssl/evp.h>

// Hash a string according to its length, put the result in hash parameter
void do_hassh(char *string, unsigned char *hash, int hash_func, int string_len){

  // if(hash_func == 2){
  //   MD5_Init(&ctx);
  //   MD5_Update(
  //     &ctx,
  //     string,
  //     string_len);
  //   MD5_Final(hash, &ctx);
  // }
}

// Verify if a hash is fitting the juggling attack
int hash_ok(unsigned char *hash, int hash_length){
  if(hash[0] != 0x0e) return 0;           // Must begin with 0x0e
  
  for(int i = 1; i < hash_length; i++){   // The following is letterless
    if((hash[i]&(0xf))>>1 > 4) return 0;
    if(hash[i]>>5 > 4) return 0;
  }
  return 1;
}

void do_hash(char *string, unsigned char *hash, int hash_func, int string_len){
  EVP_MD_CTX* context = EVP_MD_CTX_new();
  const EVP_MD* md = EVP_md5();
  unsigned int  md_len;

  EVP_DigestInit_ex2(context, md, NULL);
  EVP_DigestUpdate(context, string, string_len);
  EVP_DigestFinal_ex(context, hash, &md_len);
  EVP_MD_CTX_free(context);
}