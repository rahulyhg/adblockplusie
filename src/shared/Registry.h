#ifndef REGISTRY_H
#define REGISTRY_H

#include <string>
#include <Windows.h>

namespace AdblockPlus
{
  /**
   * An open key in the system registry.
   *
   * This class is not completely general.
   * In particular, it cannot encapsulate the predefined registry keys
   *   such as HKEY_CLASSES_ROOT.
   * These classes are considered "always open",
   *   and the destructor should not close them.
   * Rather than trying to detect these predefined keys,
   *   we simply don't allow them to be constructed.
   * In practice, this is a limitation without much consequence.
   * If this were a library designed for standalone use,
   *   this limitation might not be appropriate, but it's fine here.
   */
  class RegistryKey
  {
    /**
     * Handle to registry key that is open and not predefined.
     */
    HKEY key;

  public:
    /**
     * Constructor to open a key as a subkey key of an existing parent.
     * Opens the key with read-only access.
     *
     * The constructor throws if 'key_name' is not found,
     *   to preserve the invariant that the registry key is open.
     * The constructor also throws if 'key_name' is empty,
     *   to preserve the invariant the the registry key is not predefinded.
     *
     * \param parent
     *   An open registry key. This may be one of the predefined keys.
     * \param key_name
     *   Name of the subkey to be opened under the parent.
     */
    RegistryKey(HKEY parent, const std::wstring& key_name);

    /**
     * Destructor always closes the key.
     */
    ~RegistryKey();

    /**
     * Retrieve a value from a name-value pair within the present key.
     *
     * Throws if the name is not found within the dictionary.
     * Throws if the name is found but is not a string.
     */
    std::wstring value_wstring(const std::wstring& name) const;
  };
}

#endif