package HomeWork.MyT;

import java.util.*;
import java.util.regex.*;


public class CheckAnswer {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        StringBuilder inputText = new StringBuilder();

        while (scanner.hasNextLine()) {
            inputText.append(scanner.nextLine()).append("\n");
        }
        scanner.close();

        Pattern pattern = Pattern.compile("第\\s*(\\d+)\\s*题[\\s\\S]*?您已选\\s*([A-Z,]+)\\s*√");
        Matcher matcher = pattern.matcher(inputText);

        Map<Integer, String> results = new TreeMap<>();

        while (matcher.find()) {
            int questionNum = Integer.parseInt(matcher.group(1));
            String answer = matcher.group(2);
            results.put(questionNum, answer);
        }

        StringBuilder output = new StringBuilder();
        for (Map.Entry<Integer, String> entry : results.entrySet()) {
            output.append(String.format("第%d题   %s；", entry.getKey(), entry.getValue()));
        }

        System.out.println(output.toString());
    }
}
