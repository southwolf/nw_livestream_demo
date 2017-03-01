{
  "targets": [
    {
      "target_name": "live",
      "sources": [
        "sdk.cc"
      ],
      "include_dirs": [
        "sdk/include"
      ],
      "library_dirs": [
        "sdk/lib/win32"
      ],
      "libraries": [
        "/lSMediaCapture.lib"
      ]
      # ],
      #  "copies": [
      #    {
      #      "destination": "<(module_root_dir)/",
      #      "files": ["<(module_root_dir)/sdk/lib/win32/"]
      #    }
      #  ]
    }
  ]
}