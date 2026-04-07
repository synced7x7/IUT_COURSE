import { useAuth } from "../context/AuthContext";
import { useNavigate } from "react-router-dom";

export default function Dashboard() {
  const { user, token, logout } = useAuth();
  const navigate = useNavigate();

  console.log("JWT:", token);

  return (
    <div>
      <h2>Dashboard</h2>
      <p>Welcome, {user?.email || "Guest"}! </p>
      <button onClick={() => navigate("/settings")}>
        Go to Settings
      </button>
      <button onClick={logout}>
        Logout
      </button>
    </div>
  );
}