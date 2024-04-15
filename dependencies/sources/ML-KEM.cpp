#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Fonction pour générer des octets aléatoires
std::vector<uint8_t> generate_random_bytes(size_t num_bytes) {
    std::vector<uint8_t> bytes(num_bytes);
    for (size_t i = 0; i < num_bytes; i++) {
        bytes[i] = static_cast<uint8_t>(rand());
    }
    return bytes;
}

// Fonction pour générer les clés d'encapsulation et de décapsulation
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> MLKEM_KeyGen(size_t k) {
    std::vector<uint8_t> ek;
    std::vector<uint8_t> dk;

    // 1: z ← $ ▷ z is 32 random bytes (see Section 3.3)
    std::vector<uint8_t> z = generate_random_bytes(32);

    // 2: (ekPKE,dkPKE) ← K-PKE.KeyGen() ▷ run key generation for K-PKE
    // (Simulons la génération des clés ekPKE et dkPKE)
    std::vector<uint8_t> ekPKE = keygen(); // TODO: Mettre la bonne fonction de génération de clé
    std::vector<uint8_t> dkPKE = keygen(); // TODO: Mettre la bonne fonction de génération de clé

    // 3: ek ← ekPKE ▷ KEM encaps key is just the PKE encryption key
    ek = ekPKE;

    // 4: dk ← (dkPKE∥ek∥H(ek)∥z) ▷ KEM decaps key includes PKE decryption key
    // (Simulons la fonction de hachage H(ek))
    std::vector<uint8_t> H_ek = generate_random_bytes(32); // TODO: Mettre les bonnes fonctions de hachage

    dk.reserve(dkPKE.size() + ek.size() + H_ek.size() + z.size());
    dk.insert(dk.end(), dkPKE.begin(), dkPKE.end());
    dk.insert(dk.end(), ek.begin(), ek.end());
    dk.insert(dk.end(), H_ek.begin(), H_ek.end());
    dk.insert(dk.end(), z.begin(), z.end());

    // 5: return (ek,dk)
    return std::make_pair(ek, dk);
}

// Fonction d'encapsulation
std::pair<std::vector<uint8_t>, std::vector<uint8_t>> MLKEM_Encap(const std::vector<uint8_t>& ek) {
    // 1: m ← $ ▷ m is 32 random bytes (see Section 3.3)
    std::vector<uint8_t> m = generate_random_bytes(32);

    // 2: (K, r) ← G(m∥H(ek)) ▷ derive shared secret key K and randomness r
    std::vector<uint8_t> m_H_ek(m.size() + H(ek).size()); // Mettre la vrai fonction de hachage (à la place de H(ek)) 
    std::copy(m.begin(), m.end(), m_H_ek.begin()); // Cela sert à concaténer les vecteurs m et H(ek)
    std::copy(H(ek).begin(), H(ek).end(), m_H_ek.begin() + m.size()); // PErmet de copier H(ek) à la suite de m
    std::pair<std::vector<uint8_t>, std::vector<uint8_t>> K_r = G(m_H_ek); // Mettre la vrai fonction G
    std::vector<uint8_t> K = K_r.first;
    std::vector<uint8_t> r = K_r.second;

    // 3: c ← K-PKE.Encrypt(ek, m, r) ▷ encrypt m using K-PKE with randomness r
    std::vector<uint8_t> c = K_PKE_Encrypt(ek, m, r);

    // 4: return (K, c)
    return std::make_pair(K, c);
}

// Fonction de décapsulation
std::vector<uint8_t> MLKEM_Decap(const std::vector<uint8_t>& dk, const std::vector<uint8_t>& c) {
    size_t k = 32;  // Longueur de la clé d'encapsulation (supposée être 32 octets)

    // 1: dkPKE ← dk[0 : 384k] ▷ extract (from KEM decaps key) the PKE decryption key
    std::vector<uint8_t> dkPKE(dk.begin(), dk.begin() + 384 * k);

    // 2: ekPKE ← dk[384k : 768k + 32] ▷ extract PKE encryption key
    std::vector<uint8_t> ekPKE(dk.begin() + 384 * k, dk.begin() + 768 * k + 32);

    // 3: h ← dk[768k + 32 : 768k + 64] ▷ extract hash of PKE encryption key
    std::vector<uint8_t> h(dk.begin() + 768 * k + 32, dk.begin() + 768 * k + 64);

    // 4: z ← dk[768k + 64 : 768k + 96] ▷ extract implicit rejection value
    std::vector<uint8_t> z(dk.begin() + 768 * k + 64, dk.begin() + 768 * k + 96);

    // 5: m′ ← K-PKE.Decrypt(dkPKE, c) ▷ decrypt ciphertext
    std::vector<uint8_t> m_prime = K_PKE_Decrypt(dkPKE, c);

    // 6: (K′, r′) ← G(m′ ∥h)
    std::vector<uint8_t> m_prime_h(m_prime.size() + h.size());
    std::copy(m_prime.begin(), m_prime.end(), m_prime_h.begin());
    std::copy(h.begin(), h.end(), m_prime_h.begin() + m_prime.size());
    std::pair<std::vector<uint8_t>, std::vector<uint8_t>> K_prime_r_prime = G(m_prime_h);
    std::vector<uint8_t> K_prime = K_prime_r_prime.first;
    std::vector<uint8_t> r_prime = K_prime_r_prime.second;

    // 7: K¯ ← J(z∥c, 32)
    std::vector<uint8_t> z_c(z.size() + c.size());
    std::copy(z.begin(), z.end(), z_c.begin());
    std::copy(c.begin(), c.end(), z_c.begin() + z.size());
    std::vector<uint8_t> K_bar = J(z_c, 32);

    // 8: c′ ← K-PKE.Encrypt(ekPKE, m′, r′) ▷ re-encrypt using the derived randomness r′
    std::vector<uint8_t> c_prime = K_PKE_Encrypt(ekPKE, m_prime, r_prime);

    // 9: if c = c′ then
    if (c == c_prime) {
        // 10: K′ ← K¯ ▷ if ciphertexts do not match, "implicitly reject"
        K_prime = K_bar;
    }

    // 12: return K′
    return K_prime;
}    