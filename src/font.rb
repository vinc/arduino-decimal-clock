require 'erb'

# Import font in portable bitmap format
font = []
n = 16
y = 0
width = height = 0
path = File.join(File.dirname(__FILE__), 'font.pbm')
File.open(path).each_with_index do |line, index|
  line.chomp!
  if index == 0
    next if line == 'P1'
    puts 'Error: file is not in portable bitmap format'
    exit(1)
  end
  case line
  when /^#/
  when /^(?<width>\d+) (?<height>\d+)$/
    y = 0
    width = $~[:width].to_i
    height = $~[:height].to_i
    size = (width * height) / n
    font << ([0] * size)
  when /^([01]\s){3,}/
    line.split.each_with_index do |value, x|
      i = width * y + x
      case value
      when '0'
        font[-1][i / n] &= ~(1 << (i % n))
      when '1'
        font[-1][i / n] |= (1 << (i % n))
      else
        puts "Error: cols #{x} of line #{index} is not valid"
      end
    end
    y += 1
  else
    puts "Error: line #{index} is not valid"
  end
end

# Generate C array declaration
glyphes = font.map do |glyph|
  glyph.each_with_index.map do |line, y|
    '        0x%04x' % line
  end.join(",\n")
end.join("\n    }, {\n")
glyphes = "{\n#{glyphes}\n    }"

# Write C header file
path = File.join(File.dirname(__FILE__), 'font.h')
File.open(path, 'w') do |file|
  file.write(ERB.new(File.read("#{path}.erb")).result)
end
