#include "crow.h"

crow::LogLevel get_log_level_from_env() {
    const char* level = std::getenv("CROW_LOG_LEVEL");

    if (!level) return crow::LogLevel::Info; // Default

    std::string lvl(level);
    
    if (lvl == "Debug") return crow::LogLevel::Debug;
    if (lvl == "Info") return crow::LogLevel::Info;
    if (lvl == "Warning") return crow::LogLevel::Warning;
    if (lvl == "Error") return crow::LogLevel::Error;
    if (lvl == "Critical") return crow::LogLevel::Critical;
    return crow::LogLevel::Info;
}

int main(int argc, char *argv[]) {
    crow::SimpleApp app;
    
    
    if (argc < 3)
    {
        std::cerr<< argv[0] << ": <IP> <Port>" <<  std::endl;
        return EXIT_FAILURE;
    }
    int port = atoi(argv[2]);
    
    if (port > UINT16_MAX)
    {
        std::cerr<< "Invalid port :" << port <<  std::endl;
        return EXIT_FAILURE;
    }

    app.loglevel(get_log_level_from_env());

    CROW_WEBSOCKET_ROUTE(app, "/ws")
        .onaccept([](const crow::request&, void**){
            return true;
        })
        .onopen([](crow::websocket::connection& conn){
            std::cout << "WebSocket opened" << std::endl;
            conn.send_text("Hello: ");
        })
        .onmessage([](crow::websocket::connection& conn, const std::string& msg, bool){
            conn.send_text("Echo: " + msg);
        })
        .onclose([](crow::websocket::connection& conn, const std::string& reason, 
                    uint16_t code){
            std::cout << "WebSocket closed: " << reason << " (" << code << ")"
                        << std::endl;
            if ( code == crow::websocket::NormalClosure )
            {
                conn.close();
            }
        })
        .onerror([](crow::websocket::connection& conn, 
                const std::string& error) {
         std::cerr << "Error: " << error << std::endl;
        
        });
        
    try {
        app.port(port).bindaddr(argv[1]).run();
    } catch (const std::exception& e) {
        std::cerr << "Server failed: " << e.what() << std::endl;
    }

}
