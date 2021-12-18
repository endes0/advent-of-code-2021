#include <iostream>
#include <string>

unsigned int decode_binary(std::string binary) {
  unsigned int result = 0;
  for (auto c : binary) {
    result = result << 1;
    if (c == '1') {
      result++;
    }
  }

  return result;
}

int parse_stream_packets(std::string stream, bool first, int until,
                         size_t &last_pos) {
  int result = 0;

  size_t pos = (until == -1) ? 0 : last_pos;
  size_t parsed = 0;
  while (pos < stream.size() && (until == -1 || parsed < until)) {
    if (first && stream.size() - 1 - pos < 11) {
      break;
    }

    unsigned int version = decode_binary(stream.substr(pos, 3));
    unsigned int type = decode_binary(stream.substr(pos + 3, 3));
    pos += 6;

    result += version;

    switch (type) {
      case 4: {
        size_t internal_pos = pos;
        do {
          /* code */

          if (stream[internal_pos] == '0') {
            break;
          }
          internal_pos += 5;
        } while (true);

        pos = internal_pos + 5;
      } break;
      default: {
        if (stream[pos] == '1') {
          unsigned int until = decode_binary(stream.substr(pos + 1, 11));
          pos += 12;
          result += parse_stream_packets(stream, false, until, pos);

        } else {
          size_t useless_pos = pos;
          unsigned int packet_len = decode_binary(stream.substr(pos + 1, 15));
          pos += 16;
          result += parse_stream_packets(stream.substr(pos, packet_len), false,
                                         -1, useless_pos);
          pos += packet_len;
        }

        break;
      }
    }

    parsed++;
  }

  last_pos = pos;
  return result;
}

int main(int argc, char const *argv[]) {
  std::string stream;

  std::string line;
  std::getline(std::cin, line);

  for (auto c : line) {
    switch (c) {
      case '0':
        stream += "0000";
        break;
      case '1':
        stream += "0001";
        break;
      case '2':
        stream += "0010";
        break;
      case '3':
        stream += "0011";
        break;
      case '4':
        stream += "0100";
        break;
      case '5':
        stream += "0101";
        break;
      case '6':
        stream += "0110";
        break;
      case '7':
        stream += "0111";
        break;
      case '8':
        stream += "1000";
        break;
      case '9':
        stream += "1001";
        break;
      case 'A':
        stream += "1010";
        break;
      case 'B':
        stream += "1011";
        break;
      case 'C':
        stream += "1100";
        break;
      case 'D':
        stream += "1101";
        break;
      case 'E':
        stream += "1110";
        break;
      case 'F':
        stream += "1111";
        break;
      default:
        break;
    }
  }

  size_t discard;
  std::cout << parse_stream_packets(stream, true, -1, discard) << std::endl;

  return 0;
}
