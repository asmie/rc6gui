#include "aes_defs.h"

/// <summary>
/// Enumeration that describes cipher mode.
/// </summary>
enum class CipherMode {
	ECB = 1,
	CBC = 2,
	CFB = 3,
	OFB = 4
};

/// <summary>
/// Class that wraps raw, low-level RC6 algorithm into managed one.
/// </summary>
ref class RC6algo
{
public:
	/// <summary>
	/// Default class constructor.
	/// </summary>
	RC6algo();
	
	/// <summary>
	/// Constructor with ability to set key and its length.
	/// </summary>
	/// <param name="key">Key written in plaintext</param>
	/// <param name="keyLength">Length of the key</param>
	RC6algo(System::String^ key, int keyLength);

	/// <summary>
	/// Constructor with ability to set key, its length and cipher mode.
	/// </summary>
	/// <param name="key"></param>
	/// <param name="keyLength"></param>
	/// <param name="typ_szyfrowania"></param>
	RC6algo(System::String^ key, int keyLength, CipherMode cipherMode);

	/// <summary>
	/// Method creates encrypted file.
	/// </summary>
	/// <param name="fileIn">File to encrypt.</param>
	/// <param name="fileOut">Encrypted filename.</param>
	void Encrypt(System::String^ fileIn, System::String^ fileOut);

	/// <summary>
	/// Method creates plaintext file from encrypted one.
	/// </summary>
	/// <param name="fileIn">Encrypted file.</param>
	/// <param name="fileOut">File to store plaintext.</param>
	/// <returns></returns>
	bool Decrypt(System::String^ fileIn, System::String^ fileOut);

private:
	array<System::Byte^>^ key_;
	array<System::Byte^>^ sessionKey_;
	array<System::Byte^>^ IV;
	CipherMode cipherMode_; 
	unsigned char keyLength_;

	// Methods that generate initial data
	void GenerateSessionKey(void);
	void GenerateIV(void);

	// Private methods that support RC6 header.
	void WriteHeader(System::String^ fileOut);
	void ReadHeader(System::String^ fileIn);

	// Private encrypt methods supporting ECB, CBC, CFB and OFB
	void Encrypt_ECB_CBC(System::String^ fileIn, System::String^ fileOut);
	bool DecryptECB_CBC(System::String^ fileIn, System::String^ fileOut);
	void EncryptCFB_OFB(System::String^ fileIn, System::String^ fileOut);
	bool Decrypt_CFB_OFB(System::String^ fileIn, System::String^ fileOut);
};