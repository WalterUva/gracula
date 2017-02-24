{
  "targets": [
    {
      "target_name": "gpio",

      "sources": [ "GPIO.cc" ],

      "include_dirs": [

        "<!(node -e \"require('nan')\")"

      ]
    }
  ]
}
