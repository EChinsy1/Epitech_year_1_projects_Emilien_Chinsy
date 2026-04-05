# Nested Easter Egg 4*:

## Description of the challenge:
Apply some advanced cryptanalysis to find the real easter egg. (Difficulty Level: 4)

## Methodology:
### Steps:
- 1: We already have the first part of the easter egg thank to the [easter_egg](../Broken%20Access%20Control/Broken%20Access%20Control-4-Easter%20Egg.md) flag. So we can read it: here is what we find. 
![inside_easter_egg](../images/easter_egg_file.png)

- 2: The real easter egg doesn't make any sense so it is probably encoded, so I used a cipher identifier to figure out how it was encoded. 
![cipher_identifier_egg](../images/cipher_identifier_egg.png)

- 3: We can see that it was encoding using Base64 Coding, so let's try decoding it:
![decode_part_one](../images/decode_esater_egg_part_one.png)

- 4: It looks like a path to a file, but the letters are jumbled, it looks like caesar cipher, so let's try to decode it again
![easter_egg](../images/ceaser_easter_egg.png)

- 5: this looks like the rest of a URL, so we add it after the site URL and we get the result
![nested_easter_egg](../images/nested_easter_egg.png)

### Techniques:
- Research
- Cryptography

### Tools:
- [Dcode](https://www.dcode.fr/cipher-identifier)
## Vulnerabilities:

### Name: 
Cryptographic Issues
### Affected components:
- None
### Severity Level:
- None, this is an easter egg

## Risks:
### Impact:
- None as it is an easter egg

## Actions:
### Risk mitigation strategies:
- Don't leave an easter egg in the files
### Remediation fixes:
- Don't leave an easter egg in the files
### Related best security practices
- Don't leave an easter egg in the files
