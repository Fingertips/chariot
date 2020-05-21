# frozen_string_literal: true

$LOAD_PATH.unshift File.expand_path('lib', __dir__)
require 'chariot/version'

Gem::Specification.new do |spec|
  spec.name     = 'chariot'
  spec.version  = Chariot::VERSION
  spec.licenses = ['MIT']

  spec.summary  = 'Ruby wrapper for os_signposts'
  spec.description = 'Ruby wrapper for os_signposts used to record events ' \
                     'and intervals and show them using Xcode Instruments.'
  spec.authors  = ['Manfred Stienstra']
  spec.homepage = 'http://github.com/Fingertips/chariot'
  spec.email = ['manfred@fngtps.com']

  # spec.extensions << 'ext/extconf.rb'
  spec.files = Dir.glob('{bin,lib,ext}/**/*') + [
    'README.md',
    'LICENSE'
  ]
  spec.extra_rdoc_files = %w[
    README.md
    LICENSE
  ]
end
